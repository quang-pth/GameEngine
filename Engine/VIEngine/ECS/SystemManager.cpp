#include"SystemManager.h"
#include"ECS/Coordinator.h"
#include"Core/Time/Time.h"
#include"Memory/MemoryMonitor.h"

namespace VIEngine {
	namespace ECS {
		DEFINE_RTTI_NO_PARENT(SystemManager)

		SystemManager::SystemManager() : MemoryManager(), mSystemIdx(0), mRebuildSystemWorkOrder(false) {

		}

		SystemManager::SystemManager(Coordinator* coordinator) : MemoryManager(), mCoordinator(coordinator), mSystemIdx(0), mRebuildSystemWorkOrder(false) {

		}

		SystemManager::~SystemManager() {

		}

		void SystemManager::OnInit() {
			if (mRebuildSystemWorkOrder) {
				BuildSystemWorkOrder();
				mRebuildSystemWorkOrder = false;
			}

			for (auto system : mSortedOrderSystems) {
				system->OnInit();
			}
		}

		void SystemManager::OnUpdate(Time time) {
			if (mRebuildSystemWorkOrder) {
				BuildSystemWorkOrder();
				mRebuildSystemWorkOrder = false;
			}

			for (auto system : mSortedOrderSystems) {
				if (system->GetUpdateInterval() < 0.0f) {
					system->OnUpdate(time);
					continue;
				}

				float intervalPassBy = system->GetLastUpdateTime() + time.GetDeltaTime();
				//CORE_LOG_TRACE("intervalPassBy {0}", intervalPassBy);
				if (intervalPassBy > system->GetUpdateInterval()) {
					system->OnUpdate(time);
					intervalPassBy -= system->GetUpdateInterval();
					//CORE_LOG_TRACE("intervalPassBy remain {0}", intervalPassBy);
				}
		
				system->SetLastUpdateTime(intervalPassBy);
			}
		}

		void SystemManager::OnShutdown() {
			for (auto iter = mUnsortedOrderSystems.rbegin(); iter != mUnsortedOrderSystems.rend(); iter++) {
				(*iter)->OnShutdown();
				FreeOnStack(*iter);
			}
			MemoryMonitor::Get().Remove(this);
		}

		void SystemManager::BuildSystemWorkOrder() {
			mSortedOrderSystems.clear();

			enum class EVertexState {
				None, Visited, Done
			};

			using VertexTraverseStates = std::vector<EVertexState>;
			using TraversalPath = std::vector<SystemID>;
			using SystemPriorityGroups = std::unordered_map<ESystemPriority, std::vector<SystemID>>;

			VertexTraverseStates traversalStates(mSystemIdx, EVertexState::None);

			std::function<void(SystemID, VertexTraverseStates&, DependenciesMatrix&, TraversalPath&)> depthFirstSearch =
				[&](SystemID vertex, VertexTraverseStates& vertexStates, DependenciesMatrix& dependencies, TraversalPath& path)
				{
					vertexStates[vertex] = EVertexState::Visited;

					for (SystemID neighbor = 0; neighbor < dependencies[vertex].size(); neighbor++) {
						if (
							vertexStates[neighbor] == EVertexState::Visited
							|| vertexStates[neighbor] == EVertexState::Done
						) continue;

						if (dependencies[vertex][neighbor]) {
							depthFirstSearch(neighbor, traversalStates, dependencies, path);
						}
					}

					path.push_back(vertex);
					vertexStates[vertex] = EVertexState::Done;
				};

			SystemPriorityGroups systemGroups;
			for (uint8_t i = 0; i < mSystemIdx; i++) {
				ISystem* system = mUnsortedOrderSystems[i];
				systemGroups[system->GetPriority()].push_back(system->GetID());
			}

			std::multimap<ESystemPriority, std::vector<SystemID>> sortedGroups;
			// Starting Topological sort
			for (auto& [priority, systems] : systemGroups) {
				TraversalPath path;

				for (SystemID id : systems) {
					if (traversalStates[id] != EVertexState::Done) {
						depthFirstSearch(id, traversalStates, mDependenciesMatrix, path);
					}
				}

				sortedGroups.insert({ priority, path });
			}

			for (auto& [priority, path] : sortedGroups) {
				for (SystemID id : path) {
					mSortedOrderSystems.push_back(mUnsortedOrderSystems[id]);
				}
			}
		}

	} // namespace ECS
} // namespace VIEngine
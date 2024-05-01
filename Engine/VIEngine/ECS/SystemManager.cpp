#include"SystemManager.h"
#include"Memory/Allocator/MemoryAllocator.h"
#include"Coordinator.h"

namespace VIEngine {
	namespace ECS {
		SystemManager::SystemManager() : GlobalMemory(), mSystemIdx(0), mRebuildWorkOrder(false) {
		
		}

		SystemManager::SystemManager(Coordinator* coordinator) : mCoordinator(coordinator), mSystemIdx(0), mRebuildWorkOrder(false) {

		}

		SystemManager::~SystemManager() {

		}

		void SystemManager::Init() {
			GlobalMemory::Init(EMemoryAllocator::Linear);
		}

		void SystemManager::OnUpdate(Time time) {
			if (mRebuildWorkOrder) {
				mSortedOrderSystems.clear();
				BuildSystemWorkOrder();
				mRebuildWorkOrder = false;
			}

			for (auto system : mSortedOrderSystems) {

				if (system->GetUpdateInterval() < 0.0f) {
					system->OnUpdate(time);
					continue;
				}

				float intervalPassBy = system->GetLastUpdateTime() + time.GetDeltaTime();
				float systemUpdateInterval = system->GetUpdateInterval();

				if (intervalPassBy > systemUpdateInterval) {
					system->OnUpdate(time.GetDeltaTime());
					intervalPassBy -= systemUpdateInterval;
				}

				system->SetLastUpdateTime(intervalPassBy);
			}
		}

		void SystemManager::Shutdown() {
			GlobalMemory::Shutdown();
		}

		void SystemManager::BuildSystemWorkOrder() {
			enum class EVertexState {
				None,
				Visited,
				Done
			};

			using VertexTraverseStates = std::vector<EVertexState>;
			using TraversalPath = std::vector<SystemID>;
			using SystemPriortyGroups = std::unordered_map<ESystemPriority, std::vector<SystemID>>;

			VertexTraverseStates traversalStates(mSystemIdx, EVertexState::None);

			std::function<void (SystemID, VertexTraverseStates&, DependenciesMatrix&, TraversalPath&)> depthFirstSearch = 
					[&](SystemID vertex, VertexTraverseStates& vertexStates, DependenciesMatrix& dependencies, TraversalPath& path)
			{
				vertexStates[vertex] = EVertexState::Visited;

				for (SystemID neighbor = 0; neighbor < dependencies[vertex].size(); neighbor++) {
					if (vertexStates[neighbor] == EVertexState::Visited) continue;
					if (vertexStates[neighbor] == EVertexState::Done) continue;

					if (dependencies[vertex][neighbor]) {
						depthFirstSearch(neighbor, traversalStates, dependencies, path);
					}
				}

				path.emplace_back(vertex);
				vertexStates[vertex] = EVertexState::Done;
			};

			SystemPriortyGroups systemGroups;
			for (uint8_t i = 0; i < mSystemIdx; i++) {
				systemGroups[mUnsortedOrderSystems[i]->GetPriority()].emplace_back(mUnsortedOrderSystems[i]->GetID());
			}

			std::multimap<ESystemPriority, std::vector<SystemID>> sortedGroups;
			// Topological Sort
			for (auto& [priority, systems] : systemGroups) {
				TraversalPath path;

				for (SystemID id : systems) {
					if (traversalStates[id] == EVertexState::None) {
						depthFirstSearch(id, traversalStates, mDependenciesMatrix, path);
					}
				}

				std::reverse(path.begin(), path.end());

				sortedGroups.insert({priority, path});
			}

			for (auto& [priority, path] : sortedGroups) {
				for (SystemID systemID : path) {
					mSortedOrderSystems.emplace_back(mUnsortedOrderSystems[systemID]);
				}
			}
		}

	} // namespace ECS
} // namespace VIEngine
#pragma once

#include"ISystem.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
	namespace ECS {
		class VI_API SystemManager : public GlobalMemory {
			using DependenciesMatrix = std::vector<std::vector<bool>>;
		public:
			SystemManager();
			SystemManager(class Coordinator*);
			~SystemManager();

			void Init();
			void OnUpdate(Time);
			void Shutdown();

			template<typename T>
			T& AddSystem() {
				VI_BASE_CLASS_STATIC_ASSERT(ISystem, T, "Not standard system type");

				void* address = Allocate(sizeof(T), alignof(T), "SystemManager");
				ISystem* system = new (address)T();
				system->SetID(mSystemIdx++);
				system->SetCoordinator(mCoordinator);

				mSystemMap[T::GetStaticTypeID()] = system;
				mUnsortedOrderSystems.emplace_back(system);

				CORE_LOG_INFO("{0} is added with ID {1}", T::GetStaticTypeString(), system->GetID());

				mDependenciesMatrix.resize(mSystemIdx);
				for (uint8_t i = 0; i < mDependenciesMatrix.size(); i++) {
					mDependenciesMatrix[i].resize(mSystemIdx);
				}

				mRebuildWorkOrder = true;

				return *static_cast<T*>(system);
			}

			template<typename T>
			T& GetSystem() {
				VI_BASE_CLASS_STATIC_ASSERT(ISystem, T, "Not standard system type");

				SystemTypeID systemTypeID = T::GetStaticTypeID();
				VI_ASSERT(mSystemMap.count(systemTypeID) && "Get non-existing system");
				
				return *static_cast<T*>(mSystemMap.at(systemTypeID));
			}

			template<typename T, typename Dependency>
			void AddSystemDependency(T* system, Dependency* dependency) {
				VI_BASE_CLASS_STATIC_ASSERT(ISystem, T, "Not standard system type");
				VI_BASE_CLASS_STATIC_ASSERT(ISystem, Dependency, "Not standard system type");

				SystemID targetID = system->GetID();
				SystemID dependencyID = dependency->GetID();

				mDependenciesMatrix[dependencyID][targetID] = true;
				CORE_LOG_INFO("{1} is added as a dependency of {0}", Dependency::GetStaticTypeString(), T::GetStaticTypeString());
			}

			template<typename T, typename Dependency, typename... Dependencies>
			void AddSystemDependency(T* system, Dependency* dependency, Dependencies&&... dependencies) {
				VI_BASE_CLASS_STATIC_ASSERT(ISystem, T, "Not standard system type");
				VI_BASE_CLASS_STATIC_ASSERT(ISystem, Dependency, "Not standard system type");

				SystemID targetID = system->GetID();
				SystemID dependencyID = dependency->GetID();

				mDependenciesMatrix[dependencyID][targetID] = true;
				CORE_LOG_INFO("{1} is added as a dependency of {0}", Dependency::GetStaticTypeString(), T::GetStaticTypeString());
				AddSystemDependency(system, std::forward<Dependencies>(dependencies)...);
			}

			void BuildSystemWorkOrder();

		private:
			std::unordered_map<SystemTypeID, ISystem*> mSystemMap;
			std::vector<ISystem*> mUnsortedOrderSystems;
			std::vector<ISystem*> mSortedOrderSystems;
			SystemID mSystemIdx;
			DependenciesMatrix mDependenciesMatrix;
			class Coordinator* mCoordinator;
			bool mRebuildWorkOrder;
		};
	} // namespace ECS
} // namespace VIEngine
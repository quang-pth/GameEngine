#pragma once

#include"ISystem.h"
#include"Memory/MemoryManager.h"
#include"Core/Logger/Logger.h"
#include"Core/Type/RTTI.h"
#include"Core/Type/Cast.h"

namespace VIEngine {
	namespace ECS {
		class SystemManager : public MemoryManager {
			using DependenciesMatrix = std::vector<std::vector<bool>>;
		public:
			DECLARE_RTTI
		public:
			SystemManager();
			SystemManager(class Coordinator*);
			~SystemManager();

			void OnInit();
			void OnUpdate(Time);
			void OnShutdown();

			template<typename T, typename... Args>
			T& AddSystem(Args&&... args) {
				VI_BASE_CLASS_ASSERT(ISystem, T, "Add not valid system type");

				ISystem* system = NewOnStack<T>(T::RunTimeType.GetTypeName(), std::forward<Args>(args)...);

				system->SetID(mSystemIdx++);
				system->SetCoordinator(mCoordinator);

				mSystemMap[T::GetStaticTypeID()] = system;
				mUnsortedOrderSystems.emplace_back(system);

				CORE_LOG_TRACE("{0} is added with ID {1}.", T::RunTimeType.GetTypeName(), system->GetID());
				mDependenciesMatrix.resize(mSystemIdx);
				for (uint8_t i = 0; i < mDependenciesMatrix.size(); i++) {
					mDependenciesMatrix[i].resize(mSystemIdx);
				}
				mRebuildSystemWorkOrder = true;

				return *StaticCast<T*>(system);
			}

			template<typename T>
			T& GetSystem() {
				VI_BASE_CLASS_ASSERT(ISystem, T, "Get not valid system type");

				SystemTypeID systemID = T::GetStaticTypeID();
				VI_ASSERT(mSystemMap.count(systemID) && "Get non-existing system");

				return *StaticCast<T*>(mSystemMap.at(systemID));
			}

			template<typename T, typename Dependency>
			void AddSystemDependency(T* target, Dependency* dependency) {
				VI_BASE_CLASS_ASSERT(ISystem, T, "Not valid system target type");
				VI_BASE_CLASS_ASSERT(ISystem, Dependency, "Not valid system dependency type");
				
				SystemID targetID = target->GetID();
				SystemID dependencyID = dependency->GetID();

				mDependenciesMatrix[targetID][dependencyID] = true;
				CORE_LOG_TRACE("{1} is added as a dependency of {0}", T::RunTimeType.GetTypeName(), Dependency::RunTimeType.GetTypeName());
			}

			template<typename T, typename Dependency, typename... Dependencies>
			void AddSystemDependency(T* target, Dependency* dependency, Dependencies&&... dependencies) {
				VI_BASE_CLASS_ASSERT(ISystem, T, "Not valid system target type");
				VI_BASE_CLASS_ASSERT(ISystem, Dependency, "Not valid system dependency type");
				
				SystemID targetID = target->GetID();
				SystemID dependencyID = dependency->GetID();

				mDependenciesMatrix[targetID][dependencyID] = true;
				CORE_LOG_TRACE("{1} is added as a dependency of {0}", T::RunTimeType.GetTypeName(), Dependency::RunTimeType.GetTypeName());
				
				AddSystemDependency(target, std::forward<Dependencies>(dependencies)...);
			}

		private:
			void BuildSystemWorkOrder();

		private:
			std::unordered_map<SystemTypeID, ISystem*> mSystemMap;
			std::vector<ISystem*> mUnsortedOrderSystems;
			std::vector<ISystem*> mSortedOrderSystems;
			SystemID mSystemIdx;
			DependenciesMatrix mDependenciesMatrix;
			class Coordinator* mCoordinator;
			bool mRebuildSystemWorkOrder;
		};
	}
}
#pragma once

#include"pch.h"
#include"ECSType.h"
#include"ComponentManager.h"
#include"EntityManager.h"
#include"SystemManager.h"

namespace VIEngine {
	namespace ECS {
		class VI_API Coordinator {
		public:
			Coordinator();
			~Coordinator();

			void OnUpdate(Time);

			template<typename T>
			ComponentManager::ComponentArray<T>& GetComponentArray() {
				return mComponentManager.GetComponentArray<T>();
			}

			template<typename T, typename... Args>
			T& AddComponent(EntityID entityID, Args&&... args) {
				return mComponentManager.AddComponent<T>(entityID, std::forward<Args>(args)...);
			}

			template<typename T>
			T& GetComponent(EntityID entityID) {
				return mComponentManager.GetComponent<T>(entityID);
			}

			template<typename T>
			bool HasComponent(EntityID entityID) {
				return mComponentManager.HasComponent<T>(entityID);
			}

			template<typename T>
			void RemoveComponent(EntityID entityID) {
				mComponentManager.RemoveComponent<T>(entityID);
			}

			template<typename T>
			T& AddSystem() { return mSystemManager.AddSystem<T>(); }

			template<typename T>
			T& GetSystem() { return mSystemManager.GetSystem<T>(); }

			template<typename T, typename Dependency>
			void AddSystemDependency(T* system, Dependency* dependency) {
				mSystemManager.AddSystemDependency(system, dependency);
			}
			
			template<typename T, typename Dependency, typename... Dependencies>
			void AddSystemDependency(T* system, Dependency* dependency, Dependencies&&... dependencies) {
				mSystemManager.AddSystemDependency(system, dependency, std::forward<Dependencies>(dependencies)...);
			}

			EntityID AddEntity();
			void AddEntity(EntityID id);
			void RemoveEntity(EntityID entityID);
			void ReleaseForReusableEntity(EntityID entityID);
		private:
			ComponentManager mComponentManager;
			EntityManager mEntityManager;
			SystemManager mSystemManager;
		};
	}
}
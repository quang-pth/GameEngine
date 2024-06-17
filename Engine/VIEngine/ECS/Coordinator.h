#pragma once

#include"pch.h"
#include"EntityManager.h"
#include"ComponentManager.h"

namespace VIEngine {
	namespace ECS {
		class Coordinator {
		public:
			Coordinator();
			~Coordinator();

			template<typename T>
			VI_FORCE_INLINE ComponentManager::ComponentArray<T>& GetComponentArray() { return mComponentManager.GetComponentArray<T>(); }
			
			template<typename T, typename... Args>
			VI_FORCE_INLINE T& AddComponent(EntityID id, Args&&... args) { return mComponentManager.AddComponent<T>(id, std::forward<Args>(args)...); }
			
			template<typename T>
			VI_FORCE_INLINE T& GetComponent(EntityID id) { return mComponentManager.GetComponent<T>(id); }

			template<typename T>
			VI_FORCE_INLINE bool HasComponent(EntityID id) { return mComponentManager.HasComponent<T>(id); }
			
			template<typename T>
			VI_FORCE_INLINE void RemoveComponent(EntityID id) { mComponentManager.RemoveComponent<T>(id); }

			EntityID AddEntity();
			void AddEntity(EntityID id);
			void RemoveEntity(EntityID id);
			void ReleaseForReuseEntity(EntityID id);

		private:
			EntityManager mEntityManager;
			ComponentManager mComponentManager;
		};
	} // namespace ECS
} // namespace VIEngine
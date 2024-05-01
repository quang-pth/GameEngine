#pragma once

#include"pch.h"
#include"ECSType.h"

namespace VIEngine {
	namespace ECS {
		class VI_API EntityManager {
		public:
			EntityManager();
			~EntityManager();

			EntityID GetNextEntity();
			void AddEntity(EntityID id);
			void RemoveEntity(EntityID id);
			void ReleaseForReusableEntity(EntityID id);
		private:
			std::unordered_set<EntityID> mEntities;
			std::queue<EntityID> mReusableEntities;
		};
	} // namespace ECS 
} // namespace VIEngine
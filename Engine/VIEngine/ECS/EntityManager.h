#pragma once

#include"pch.h"
#include"ECSType.h"

namespace VIEngine {
	namespace ECS {
		class EntityManager {
		public:
			EntityManager();
			~EntityManager();

			EntityID GetNextID();
			void AddEntity(EntityID id);
			void RemoveEntity(EntityID id);
			void ReleaseForReuse(EntityID id);
		private:
			std::unordered_set<EntityID> mEntitiesSet;
			std::queue<EntityID> mReusableIDs;
		};
	}
}
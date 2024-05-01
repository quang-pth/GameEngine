#pragma once

#include"EntityManager.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
	namespace ECS {
		EntityManager::EntityManager() {

		}

		EntityManager::~EntityManager() {

		}
		
		EntityID EntityManager::GetNextEntity() {
			EntityID nextID = INVALID_ID;

			if (!mReusableEntities.empty()) {
				nextID = mReusableEntities.front();
				mReusableEntities.pop();
			}
			else {
				nextID = GetUUID();
			}

			return nextID;
		}

		void EntityManager::AddEntity(EntityID id) {
			if (mEntities.count(id)) {
				CORE_LOG_WARN("EntityID {0} is duplicated, reject to add it to EntityManager", id);
				return;
			}
			
			mEntities.insert(id);
		}

		void EntityManager::RemoveEntity(EntityID id) {
			mEntities.erase(id);
		}

		void EntityManager::ReleaseForReusableEntity(EntityID id) {
			mEntities.erase(id);
			mReusableEntities.push(id);
		}

	} // namespace ECS 
} // namespace VIEngine
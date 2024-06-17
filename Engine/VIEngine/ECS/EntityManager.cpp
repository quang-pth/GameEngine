#include"EntityManager.h"
#include"Core/Logger/Logger.h"

namespace VIEngine { 
	namespace ECS {
		EntityManager::EntityManager() {

		}

		EntityManager::~EntityManager() {

		}

		EntityID EntityManager::GetNextID() {
			EntityID id = INVALID_ID;

			if (!mReusableIDs.empty()) {
				id = mReusableIDs.front();
				mReusableIDs.pop();
			}
			else {
				id = GetUUID();
			}

			return id;
		}

		void EntityManager::AddEntity(EntityID id) {
			if (mEntitiesSet.count(id)) {
				CORE_LOG_WARN("Insert duplicated entity id {0}", id);
				return;
			}

			mEntitiesSet.insert(id);
		}

		void EntityManager::RemoveEntity(EntityID id) {
			mEntitiesSet.erase(id);
		}

		void EntityManager::ReleaseForReuse(EntityID id) {
			mEntitiesSet.erase(id);
			mReusableIDs.push(id);
		}
	} // namespace ECS
} // namespace VIEngine
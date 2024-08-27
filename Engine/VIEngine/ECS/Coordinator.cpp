#include"Coordinator.h"

namespace VIEngine {
	namespace ECS {
		DEFINE_RTTI_NO_PARENT(Coordinator)

		Coordinator::Coordinator() : mEntityManager(), mComponentManager(), mSystemManager(this) {

		}

		Coordinator::~Coordinator() {

		}

		EntityID Coordinator::AddEntity() {
			EntityID nextID = mEntityManager.GetNextID();
			mEntityManager.AddEntity(nextID);
			return nextID;
		}

		void Coordinator::AddEntity(EntityID id) {
			mEntityManager.AddEntity(id);
		}

		void Coordinator::RemoveEntity(EntityID id) {
			mEntityManager.RemoveEntity(id);
			mComponentManager.RemoveRelatedComponents(id);
		}

		void Coordinator::ReleaseForReuseEntity(EntityID id) {
			mEntityManager.ReleaseForReuse(id);
			mComponentManager.RemoveRelatedComponents(id);
		}
	} // namespace ECS
} // namespace VIEngine
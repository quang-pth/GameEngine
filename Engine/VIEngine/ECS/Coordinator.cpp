#include"Coordinator.h"

namespace VIEngine {
	namespace ECS {
		Coordinator::Coordinator() : mComponentManager(), mEntityManager(), mSystemManager(this) {
			mSystemManager.Init();
		}

		Coordinator::~Coordinator() {
		
		}

		void Coordinator::OnUpdate(Time time) {
			mSystemManager.OnUpdate(time);
		}

		EntityID Coordinator::AddEntity() {
			EntityID nextID = mEntityManager.GetNextEntity();
			mEntityManager.AddEntity(nextID);
			return nextID;
		}

		void Coordinator::AddEntity(EntityID id) {
			mEntityManager.AddEntity(id);
		}

		void Coordinator::RemoveEntity(EntityID entityID) {
			mEntityManager.RemoveEntity(entityID);
			mComponentManager.RemoveRelatedComponents(entityID);
		}

		void Coordinator::ReleaseForReusableEntity(EntityID entityID) {
			mEntityManager.ReleaseForReusableEntity(entityID);
			mComponentManager.RemoveRelatedComponents(entityID);
		}
	} 
}
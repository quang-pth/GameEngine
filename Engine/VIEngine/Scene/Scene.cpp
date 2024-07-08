#include"Scene.h"

namespace VIEngine {
	Scene::Scene(const Shared<ECS::Coordinator>& coordinator) : mEntityIDs(), mCoordinator(coordinator) {
	
	}

	Scene::~Scene() {
		
	}

	Actor Scene::CreateActor() {
		ECS::EntityID id = mCoordinator->AddEntity();
		mEntityIDs.push_back(id);
		return Actor(id, mCoordinator);
	}

	void Scene::RemoveActor(ECS::EntityID id) {
		mCoordinator->RemoveEntity(id);
		auto iter = std::find(mEntityIDs.begin(), mEntityIDs.end(), id);
		if (iter != mEntityIDs.end()) {
			mEntityIDs.erase(iter);
		}
	}
}
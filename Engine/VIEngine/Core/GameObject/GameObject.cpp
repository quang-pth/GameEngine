#include"GameObject.h"

namespace VIEngine {
	GameObject::GameObject() : mID(INVALID_ID), mCoordinator(nullptr) {
		
	}

	GameObject::GameObject(ECS::Coordinator* coordinator) : mCoordinator(coordinator) {
		mID = mCoordinator->AddEntity();
	}

	GameObject::GameObject(ECS::EntityID id, ECS::Coordinator* coordinator) : mID(id), mCoordinator(coordinator) {
		mCoordinator->AddEntity(mID);
	}

	GameObject::~GameObject() {
	}
}
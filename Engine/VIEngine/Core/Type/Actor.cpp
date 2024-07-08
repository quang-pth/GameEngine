#include"Actor.h"

namespace VIEngine {
	DEFINE_RTTI(Actor, &Object::RunTimeType)
	
	Actor::Actor(Shared<ECS::Coordinator> coordinator) : mCoordinator(coordinator) {
		mID = mCoordinator->AddEntity();
	}
	
	Actor::Actor(ECS::EntityID id, Shared<ECS::Coordinator> coordinator) : mID(id), mCoordinator(coordinator) {
	}

	Actor::~Actor() {
	}
}
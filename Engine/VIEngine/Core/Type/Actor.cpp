#include"Actor.h"

namespace VIEngine {
	DEFINE_RTTI(Actor, Object::RunTimeType)
	
	Actor::Actor(ECS::Coordinator* coordinator) : mCoordinator(coordinator) {
		mID = mCoordinator->AddEntity();
	}
	
	Actor::Actor(ECS::EntityID id, ECS::Coordinator* coordinator) : mID(id), mCoordinator(coordinator) {
	}

	Actor::~Actor() {
	}
}
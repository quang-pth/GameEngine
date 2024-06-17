#include"Actor.h"

namespace VIEngine {
	DEFINE_RTTI(Actor, &Object::RunTimeType)
	
	Actor::Actor(ECS::Coordinator* coordinator) : mID(INVALID_ID), mCoordinator(coordinator) {

	}
	
	Actor::Actor(ECS::EntityID id, ECS::Coordinator* coordinator) : mID(id), mCoordinator(coordinator) {

	}

	Actor::~Actor() {
		mCoordinator->ReleaseForReuseEntity(mID);
	}
}
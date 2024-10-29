#include"Actor.h"
#include"Core/Component/InfoComponent.h"
#include"Core/Component/TransformComponent.h"

namespace VIEngine {
	DEFINE_RTTI(Actor, Object::RunTimeType)
	
	Actor::Actor(ECS::Coordinator* coordinator) : mCoordinator(coordinator) {
		mID = mCoordinator->AddEntity();
		AddComponent<TransformComponent>();
		AddComponent<InfoComponent>("Actor");
	}
	
	Actor::Actor(ECS::EntityID id, ECS::Coordinator* coordinator) : mID(id), mCoordinator(coordinator) {
	}

	Actor::~Actor() {
	}
}
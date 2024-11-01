#include"Actor.h"
#include"Core/Component/InfoComponent.h"
#include"Core/Component/TransformComponent.h"
#include"Core/Component/DirtySpriteComponent.h"

namespace VIEngine {
	DEFINE_RTTI(Actor, Object::RunTimeType)
	
	Actor::Actor(ECS::Coordinator* coordinator) : mCoordinator(coordinator) {
		mID = mCoordinator->AddEntity();
		AddComponent<TransformComponent>();
		AddComponent<InfoComponent>("Actor");
		AddComponent<DirtySpriteComponent>();
	}
	
	Actor::Actor(ECS::EntityID id, ECS::Coordinator* coordinator) : mID(id), mCoordinator(coordinator) {
	}

	Actor::~Actor() {
	}
}
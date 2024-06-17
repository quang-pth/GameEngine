#include"GameplayLayer.h"
#include<VIEngine/Base.h>

using namespace VIEngine;

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	MemoryManager memoryManager;
	{
		ECS::Coordinator* coordinator = memoryManager.NewOnStack<ECS::Coordinator>("Coordinator");
		Actor* actor = memoryManager.NewOnStack<Actor>("Actor", coordinator);

		actor->AddComponent<TransformComponent>(2.0f, 3.0f);
		TransformComponent& transform = actor->GetComponent<TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetX(), transform.GetY());

		transform.SetX(10.0f);
		transform.SetY(-20.0f);
		transform = actor->GetComponent<TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetX(), transform.GetY());

		if (actor->HasComponent<TransformComponent>()) {
			actor->RemoveComponent<TransformComponent>();
		}

		if (!actor->HasComponent<TransformComponent>()) {
			LOG_WARN("Actor transform component has been removed");
		}
	}
	memoryManager.ClearOnStack();
}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(Time time) {
	
}

bool GameplayLayer::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
	return false;
}


#include"GameplayLayer.h"
#include<VIEngine/Base.h>
#include<Core/System/System.h>

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	VIEngine::MemoryManager* memoryManager = new VIEngine::MemoryManager();

	{
		VIEngine::ECS::Coordinator* coordinator = memoryManager->NewOnStack<VIEngine::ECS::Coordinator>("Coordinator");
		VIEngine::Actor* actor = memoryManager->NewOnStack<VIEngine::Actor>(VIEngine::Actor::RunTimeType.GetTypeName(), coordinator);

		actor->AddComponent<VIEngine::TransformComponent>(2.0f, 3.0f);
		VIEngine::TransformComponent& transform = actor->GetComponent<VIEngine::TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetX(), transform.GetY());

		transform.SetX(10.0f);
		transform.SetY(-20.0f);
		transform = actor->GetComponent<VIEngine::TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetX(), transform.GetY());

		if (actor->HasComponent<VIEngine::TransformComponent>()) {
			actor->RemoveComponent<VIEngine::TransformComponent>();
		}

		if (!actor->HasComponent<VIEngine::TransformComponent>()) {
			LOG_WARN("Actor transform component has been removed");
		}

		memoryManager->FreeOnStack(actor);
		memoryManager->FreeOnStack(coordinator);
		coordinator->~Coordinator();
	}

	memoryManager->ClearOnStack();
}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}


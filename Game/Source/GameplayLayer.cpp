#include"GameplayLayer.h"
#include<VIEngine/Base.h>
#include<Core/System/System.h>

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	VIEngine::MemoryManager memoryManager;

	{
		auto systemManager = memoryManager.NewOnStack<VIEngine::ECS::SystemManager>("SystemManager");

		auto& collisionSystem = systemManager->AddSystem<VIEngine::CollisionResolver>();
		auto& animationSystem = systemManager->AddSystem<VIEngine::AnimationSystem>();
		auto& renderer2D = systemManager->AddSystem<VIEngine::Renderer2D>();

		systemManager->AddSystemDependency(&animationSystem, &collisionSystem);
		systemManager->AddSystemDependency(&renderer2D, &collisionSystem, &animationSystem);

		systemManager->OnInit();
		systemManager->OnUpdate(0.0f);
		systemManager->OnShutdown();
	}

	{
		VIEngine::ECS::Coordinator* coordinator = memoryManager.NewOnStack<VIEngine::ECS::Coordinator>("Coordinator");
		VIEngine::Actor* actor = memoryManager.NewOnStack<VIEngine::Actor>(VIEngine::Actor::RunTimeType.GetTypeName(), coordinator);

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
	}

	memoryManager.ClearOnStack();
}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}


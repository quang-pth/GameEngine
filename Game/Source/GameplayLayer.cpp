#include"GameplayLayer.h"
#include<VIEngine/Base.h>
#include<Core/System/System.h>

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	{
		VIEngine::Actor actor = mScene->CreateActor();
		
		actor.AddComponent<VIEngine::TransformComponent>(2.0f, 3.0f);
		VIEngine::TransformComponent& transform = actor.GetComponent<VIEngine::TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetX(), transform.GetY());

		transform.SetX(10.0f);
		transform.SetY(-20.0f);
		transform = actor.GetComponent<VIEngine::TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetX(), transform.GetY());

		if (actor.HasComponent<VIEngine::TransformComponent>()) {
			actor.RemoveComponent<VIEngine::TransformComponent>();
		}

		if (!actor.HasComponent<VIEngine::TransformComponent>()) {
			LOG_WARN("Actor transform component has been removed");
		}
	}
}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}


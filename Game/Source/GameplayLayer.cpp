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
		
		actor.AddComponent<VIEngine::TransformComponent>(2.0f, 5.0f);
		VIEngine::TransformComponent& transform = actor.GetComponent<VIEngine::TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetPosition().X, transform.GetPosition().Y);

		transform.GetPosition().X = 10.0f;
		transform.GetPosition().Y = -20.0f;
		transform = actor.GetComponent<VIEngine::TransformComponent>();
		LOG_TRACE("Actor position: ({0}, {1})", transform.GetPosition().X, transform.GetPosition().Y);

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
	using namespace VIEngine;

	static float temp = 0.0f;
	temp += time.GetDeltaTime();

	mRenderer->Submit(RENDER_COMMAND(
		{
			RendererAPI::ClearColor(Math::Sin(temp), 0.5f, Math::Cos(temp));
		}
	));
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}


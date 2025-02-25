#include"GameplayLayer.h"
#include<Renderer/Renderer.h>
#include<Core/Component/AnimatorComponent.h>
#include<Core/Component/TransformComponent.h>
#include<Core/Component/SpriteComponent.h>
#include<Core/Component/ScriptComponent.h>
#include<Resource/Sprite.h>

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	using namespace VIEngine;

	mActor = CreateActor();
	mActor.AddComponent<ScriptComponent>("Assets/Scripts/PlayerController.lua");

	// GenerateTestingAnimations();
	// GenerateTestingSprites();
}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::GenerateTestingAnimations() {
	using namespace VIEngine;

	Animation* idleAnimation = Animation::Create("ZeroIdle");
	Animation* walkAnimation = Animation::Create("ZeroWalk");

	for (uint8_t i = 0; i < 10; i++) {
		for (uint8_t j = 0; j < 10; j++) {

			Actor actor2 = CreateActor();
			TransformComponent& transformComponent = actor2.GetComponent<TransformComponent>();
			transformComponent.SetPositionX(j * 2.0f + 1.0f);
			transformComponent.SetPositionY(i * 2.0f + 1.0f);
			//transformComponent.SetRotationZ(90.0f);
			//transformComponent.SetRotationX(180.0f);
			//transformComponent.SetRotationY(180.0f);
			AnimatorComponent& animator2 = actor2.AddComponent<AnimatorComponent>();

			if (j % 2 == 0) {
				animator2.AddAnimation(idleAnimation);
				animator2.SetFPS(4);
				animator2.SetFlipVertical(true);
			}
			else {
				animator2.AddAnimation(walkAnimation);
				animator2.SetFPS(120);
				animator2.SetFlipHorizontal(true);
			}
		}
	}
}

void GameplayLayer::GenerateTestingSprites() {
	using namespace VIEngine;


	Sprite* idleSprite = Sprite::Create("Assets/Sprite/Zero/idle/idle00.png");
	Sprite* walkSprite = Sprite::Create("Assets/Sprite/Zero/walk/walk01.png");

	for (uint8_t i = 0; i < 10; i++) {
		for (uint8_t j = 0; j < 10; j++) {
			Actor actor2 = CreateActor();
			TransformComponent& transformComponent = actor2.GetComponent<TransformComponent>();
			transformComponent.SetPositionX(j * 2.0f + 1.5f);
			transformComponent.SetPositionY(i * 2.0f + 1.0f);
			SpriteComponent& spriteComponent =  actor2.AddComponent<SpriteComponent>();

			if (j % 2 == 0) {
				spriteComponent.SetSprite(idleSprite);
				spriteComponent.SetFlipVertical(true);
				spriteComponent.SetColor({ 0.3f, 0.2f, 0.5f, 1.0f });
			}
			else {
				spriteComponent.SetSprite(walkSprite);
				spriteComponent.SetFlipHorizontal(true);
				spriteComponent.SetColor({ 0.7f, 0.8f, 0.3f, 1.0f });
			}
		}
	}
}

void GameplayLayer::OnProcessInput(const VIEngine::InputState& inputState) {

}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	using namespace VIEngine;

	Renderer::ClearColor(1.0f, 0.3f, 0.6f);

	static float temp = 0.0f;
	temp += time.GetDeltaTime();
	
	Renderer::SetAlphaState(true);
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}


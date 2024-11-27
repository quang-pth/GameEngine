#include"SpriteAnimationSystem.h"
#include"ECS/Coordinator.h"
#include"Core/Component/AnimatorComponent.h"
#include"Renderer/Renderer.h"
#include"Resource/Sprite.h"
#include"Resource/Texture2D.h"
#include"Core/Component/TransformComponent.h"
#include"Core/Logger/Logger.h"
#include"Core/Application.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(SpriteAnimationSystem)

	SpriteAnimationSystem::SpriteAnimationSystem() {

	}

	SpriteAnimationSystem::SpriteAnimationSystem(ECS::SystemID id, ECS::ESystemPriority priority) : 
		ECS::System<SpriteAnimationSystem>(id, priority)
	{
	}

	SpriteAnimationSystem::~SpriteAnimationSystem() {

	}

	void SpriteAnimationSystem::OnInit() {

	}

	void SpriteAnimationSystem::OnUpdate(Time time) {
		Application& application = Application::Get();

		for (AnimatorComponent* animator : mCoordinator->GetComponentArray<AnimatorComponent>()) {
			Animation* activeAnimation = animator->GetActiveAnimation();

			float frameTime = animator->GetFrameTime() + time.GetDeltaTime();
			animator->SetFrameTime(frameTime);

			float timePerCelSeconds = 1 / animator->GetFPS();

			if (frameTime > timePerCelSeconds) {
				activeAnimation->NextFrame();
				frameTime -= timePerCelSeconds;
				animator->SetFrameTime(frameTime);
			}

			TransformComponent& transform = animator->GetOwner().GetComponent<TransformComponent>();
			Sprite* sprite = activeAnimation->CurrentFrame();

			SpriteBatch spriteBatch;
			spriteBatch.SpriteTransform = transform.GetTransform();
			spriteBatch.SpriteContext = activeAnimation->CurrentFrame();
			spriteBatch.FlipHorizontal = animator->GetFlipHorizontal();
			spriteBatch.FlipVertical = animator->GetFlipVertical();
			spriteBatch.Depth = transform.GetPosition().y / application.GetConfig().Height;

			Renderer::SubmitSpriteBatch(spriteBatch);
		}
	}

	void SpriteAnimationSystem::OnShutdown() {

	}
}
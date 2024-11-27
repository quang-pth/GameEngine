#include"SpriteRendererSystem.h"
#include"Core/Component/SpriteComponent.h"
#include"Core/Component/TransformComponent.h"
#include"Core/Application.h"
#include"Resource/Sprite.h"
#include"Resource/Shader.h"
#include"Renderer/Renderer.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(SpriteRendererSystem)

	SpriteRendererSystem::SpriteRendererSystem() {

	}

	SpriteRendererSystem::SpriteRendererSystem(ECS::SystemID id, ECS::ESystemPriority priority) :
		ECS::System<SpriteRendererSystem>(id, priority)
	{

	}

	SpriteRendererSystem::~SpriteRendererSystem() {

	}

	void SpriteRendererSystem::OnInit() {

	}

	void SpriteRendererSystem::OnUpdate(Time time) {
		Application& application = Application::Get();

		for (SpriteComponent* spriteComponent : mCoordinator->GetComponentArray<SpriteComponent>()) {
			TransformComponent& transformComponent = spriteComponent->GetOwner().GetComponent<TransformComponent>();
			Sprite* sprite = spriteComponent->GetSprite();

			SpriteBatch spriteBatch;
			spriteBatch.SpriteTransform = transformComponent.GetTransform();
			spriteBatch.SpriteContext = sprite;
			spriteBatch.FlipHorizontal = spriteComponent->GetFlipHorizontal();
			spriteBatch.FlipVertical = spriteComponent->GetFlipVertical();
			spriteBatch.Depth = transformComponent.GetPosition().y / application.GetConfig().Height;

			Renderer::SubmitSpriteBatch(spriteBatch);
		}
	}

	void SpriteRendererSystem::OnShutdown() {

	}
}
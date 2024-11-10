#include"SpriteAnimationSystem.h"
#include"ECS/Coordinator.h"
#include"Core/Component/AnimatorComponent.h"
#include"Renderer/Renderer.h"
#include"Renderer/RenderCommand.h"
#include"Resource/Shader.h"
#include"Resource/VertexArray.h"
#include"Resource/IndexBuffer.h"
#include"Resource/Sprite.h"
#include"Resource/Texture2D.h"
#include"Core/Component/TransformComponent.h"
#include"Core/Logger/Logger.h"
#include"Core/Application.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(SpriteAnimationSystem)

	SpriteAnimationSystem::SpriteAnimationSystem() : mBatchRenderer() {

	}

	SpriteAnimationSystem::SpriteAnimationSystem(ECS::SystemID id, ECS::ESystemPriority priority) : 
		ECS::System<SpriteAnimationSystem>(id, priority),
		mBatchRenderer()
	{
	}

	SpriteAnimationSystem::~SpriteAnimationSystem() {

	}

	void SpriteAnimationSystem::OnInit() {

	}

	void SpriteAnimationSystem::OnUpdate(Time time) {
		std::multimap<float, SpriteBatch> sortedSpriteBatches;

		Application& application = Application::Get();

		for (AnimatorComponent* animator : mCoordinator->GetComponentArray<AnimatorComponent>()) {
			Animation* activeAnimation = animator->GetActiveAnimation();

			float frameTime = animator->GetFrameTime() + time.GetDeltaTime();
			animator->SetFrameTime(frameTime);

			float timePerFrame = activeAnimation->GetNumsFrame() / animator->GetFPS();

			while (frameTime > timePerFrame) {
				activeAnimation->NextFrame();
				frameTime -= timePerFrame;
				animator->SetFrameTime(frameTime);
			}

			TransformComponent& transform = animator->GetOwner().GetComponent<TransformComponent>();
			Sprite* sprite = activeAnimation->CurrentFrame();
			//Shader* shader = sprite->GetShader();
			//shader->Bind();
			//shader->SetInt("image", 0);
			//shader->SetInt("flipHorizontal", sprite->GetFlipHorizontal());
			//shader->SetInt("flipVertical", sprite->GetFlipVertical());

			//glm::mat4 model = glm::mat4(1.0f);
			//model = glm::scale(model, transform.GetScale());
			//model = glm::translate(model, transform.GetPosition());
			//shader->SetMatrix4("modelMatrix", model);
			//shader->SetMatrix4("viewMatrix", camera.GetViewMatrix());
			//shader->SetMatrix4("projectionMatrix", camera.GetProjectionMatrix());
			//Renderer::ActivateTexture(0);
			//sprite->GetVertexArray()->Bind();
			//sprite->GetTexture()->Bind();
			//Renderer::DrawIndexed(sprite->GetVertexArray()->GetIndexBuffer()->GetNums());

			SpriteBatch spriteBatch(transform.GetTransform(), activeAnimation->CurrentFrame());
			spriteBatch.FlipHorizontal = animator->GetFlipHorizontal();
			spriteBatch.FlipVertical = animator->GetFlipVertical();
			sortedSpriteBatches.insert({ transform.GetPosition().y, spriteBatch}); // TODO: Divide by window height to get sprite depth
		}

		for (auto& [_, spriteBatch] : sortedSpriteBatches) {
			mBatchRenderer.InsertBatch(spriteBatch);
		}

		mBatchRenderer.Submit();
		mBatchRenderer.Clear();
	}

	void SpriteAnimationSystem::OnShutdown() {

	}
}
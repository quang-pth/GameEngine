#include"SpriteAnimationSystem.h"
#include"ECS/Coordinator.h"
#include"Core/Component/AnimatorComponent.h"
#include"Renderer/Renderer.h"
#include"Renderer/RenderCommand.h"
#include"Resource/Shader.h"
#include"Resource/VertexArray.h"
#include"Resource/IndexBuffer.h"
#include"Core/Component/TransformComponent.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(SpriteAnimationSystem)

	SpriteAnimationSystem::SpriteAnimationSystem() : mRenderBatch() {

	}

	SpriteAnimationSystem::SpriteAnimationSystem(ECS::SystemID id, ECS::ESystemPriority priority) : 
		ECS::System<SpriteAnimationSystem>(id, priority),
		mRenderBatch()
	{
	}

	SpriteAnimationSystem::~SpriteAnimationSystem() {

	}

	void SpriteAnimationSystem::OnInit() {

	}

	void SpriteAnimationSystem::OnUpdate(Time time) {
		mRenderBatch.Clear();

		for (AnimatorComponent* animator : mCoordinator->GetComponentArray<AnimatorComponent>()) {
			Animation* activeAnimation = animator->GetActiveAnimation();

			if (activeAnimation == nullptr) return;

			float runtime = animator->GetRuntime() + time.GetDeltaTime();
			animator->SetRuntime(runtime);

			float fpsPerTexture = animator->GetFPS() / activeAnimation->GetNumsFrame();
			float timePerTexture = 1.0f / fpsPerTexture;

			while (runtime > timePerTexture) {
				activeAnimation->NextFrame();
				runtime -= timePerTexture;
				animator->SetRuntime(runtime);
			}

			//if (!mRenderBatches.size() || !mRenderBatches.back().HasSlot()) {
			//	mRenderBatches.emplace_back();
			//}

			//Shader* shader = animator->GetShader();
			//shader->Bind();
			//shader->SetInt("image", 0);
			//shader->SetInt("flipHorizontal", animator->GetFlipHorizontal());
			//shader->SetInt("flipVertical", animator->GetFlipVertical());
			//animator->GetVertexArray()->Bind();

			TransformComponent& transform = animator->GetOwner().GetComponent<TransformComponent>();
			
			Texture2D* texture = activeAnimation->CurrentFrame();
			texture->SetWrapMode(ETextureWrapMode::Clamp, ETextureWrapMode::Clamp);
			//texture->Bind();
			//Renderer::DrawIndexed(animator->GetVertexArray()->GetIndexBuffer()->GetNums());
			// RenderBatch::Draw(vertexBuffer, indexBuffer);
			Vertex* vertices = (Vertex*)animator->GetVertexArray()->GetVertexBuffer()->GetData();
			uint32_t* indices = (uint32_t*)animator->GetVertexArray()->GetIndexBuffer()->GetData();
			mRenderBatch.InsertBatch(transform.GetTransform(), vertices, indices, texture, animator->GetFlipVertical(), animator->GetFlipHorizontal());
		}

		mRenderBatch.Submit();
	}

	void SpriteAnimationSystem::OnShutdown() {

	}
}
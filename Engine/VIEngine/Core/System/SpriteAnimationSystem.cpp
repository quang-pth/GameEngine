#include"SpriteAnimationSystem.h"
#include"ECS/Coordinator.h"
#include"Core/Component/AnimatorComponent.h"
#include"Renderer/Renderer.h"
#include"Renderer/RenderCommand.h"
#include"Resource/Shader.h"
#include"Resource/VertexArray.h"
#include"Resource/IndexBuffer.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(SpriteAnimationSystem)

	SpriteAnimationSystem::SpriteAnimationSystem(ECS::SystemID id, ECS::ESystemPriority priority) : 
		ECS::System<SpriteAnimationSystem>(id, priority),
		mBatchRenderer()
	{

	}

	void SpriteAnimationSystem::OnInit() {

	}

	void SpriteAnimationSystem::OnUpdate(Time time) {
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

			Shader* shader = animator->GetShader();
			shader->Bind();
			shader->SetInt("image", 0);
			shader->SetInt("flipHorizontal", animator->GetFlipHorizontal());
			shader->SetInt("flipVertical", animator->GetFlipVertical());
			animator->GetVertexArray()->Bind();
			Texture2D* texture = activeAnimation->CurrentFrame();
			texture->SetWrapMode(ETextureWrapMode::Clamp, ETextureWrapMode::Clamp);
			texture->Bind();
			Renderer::DrawIndexed(animator->GetVertexArray()->GetIndexBuffer()->GetNums());
			// RenderBatch::Draw(vertexBuffer, indexBuffer);
		}
	}

	void SpriteAnimationSystem::OnShutdown() {

	}
}
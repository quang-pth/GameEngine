#include"SpriteAnimationSystem.h"
#include"ECS/Coordinator.h"
#include"Core/Component/AnimatorComponent.h"
#include"Renderer/Renderer.h"
#include"Renderer/RenderCommand.h"
#include"Resource/Shader.h"
#include"Resource/VertexArray.h"
#include"Resource/IndexBuffer.h"
#include"Core/Component/TransformComponent.h"
#include"Core/Logger/Logger.h"

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
		mBatchRenderer.Clear();
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
			
			Texture2D* texture = activeAnimation->CurrentFrame();
			Vertex* vertices = (Vertex*)animator->GetVertexArray()->GetVertexBuffer()->GetData();
			uint32_t* indices = (uint32_t*)animator->GetVertexArray()->GetIndexBuffer()->GetData();
			mBatchRenderer.InsertBatch(transform.GetTransform(), vertices, indices, texture, animator->GetFlipVertical(), animator->GetFlipHorizontal());
		}
		mBatchRenderer.Submit();
	}

	void SpriteAnimationSystem::OnShutdown() {

	}
}
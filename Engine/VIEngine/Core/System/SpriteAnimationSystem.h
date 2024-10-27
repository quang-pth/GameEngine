#pragma once

#include"Core/Type/RTTI.h"
#include"ECS/ISystem.h"
#include"Renderer/BatchRenderer.h"

namespace VIEngine {
	class VI_API SpriteAnimationSystem : public ECS::System<SpriteAnimationSystem> {
	public:
		DECLARE_RTTI
	public:
		SpriteAnimationSystem() = default;
		SpriteAnimationSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low);
		~SpriteAnimationSystem() = default;
		virtual void OnInit() override;
		virtual void OnUpdate(Time) override;
		virtual void OnShutdown() override;
	private:
		BatchRenderer mBatchRenderer;
	};
}
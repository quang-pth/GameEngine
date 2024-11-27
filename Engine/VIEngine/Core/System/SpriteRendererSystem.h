#pragma once

#include"Core/Type/RTTI.h"
#include"ECS/ISystem.h"
#include"Renderer/BatchRenderer.h"

namespace VIEngine {
	class VI_API SpriteRendererSystem : public ECS::System<SpriteRendererSystem> {
	public:
		DECLARE_RTTI
	public:
		SpriteRendererSystem();
		SpriteRendererSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low);
		~SpriteRendererSystem();
		virtual void OnInit() override;
		virtual void OnUpdate(Time) override;
		virtual void OnShutdown() override;
	};
}
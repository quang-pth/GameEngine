#pragma once

#include"Core/Type/RTTI.h"
#include"ECS/ISystem.h"
#include"Renderer/BatchRenderer.h"

namespace VIEngine {
	class VI_API DirtySpriteValidationSystem : public ECS::System<DirtySpriteValidationSystem> {
	public:
		DECLARE_RTTI
	public:
		DirtySpriteValidationSystem();
		DirtySpriteValidationSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low);
		~DirtySpriteValidationSystem();
		virtual void OnInit() override;
		virtual void OnUpdate(Time) override;
		virtual void OnShutdown() override;
	};
}
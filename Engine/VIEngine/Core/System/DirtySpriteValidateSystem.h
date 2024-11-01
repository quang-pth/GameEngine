#pragma once

#include"Core/Type/RTTI.h"
#include"ECS/ISystem.h"
#include"Renderer/BatchRenderer.h"

namespace VIEngine {
	class VI_API DirtySpriteValidateSystem : public ECS::System<DirtySpriteValidateSystem> {
	public:
		DECLARE_RTTI
	public:
		DirtySpriteValidateSystem();
		DirtySpriteValidateSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low);
		~DirtySpriteValidateSystem();
		virtual void OnInit() override;
		virtual void OnUpdate(Time) override;
		virtual void OnShutdown() override;
	};
}
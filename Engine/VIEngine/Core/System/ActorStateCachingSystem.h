#pragma once

#include"Core/Type/RTTI.h"
#include"ECS/ISystem.h"
#include"Renderer/BatchRenderer.h"

namespace VIEngine {
	class VI_API ActorStateCachingSystem : public ECS::System<ActorStateCachingSystem> {
	public:
		DECLARE_RTTI
	public:
		ActorStateCachingSystem();
		ActorStateCachingSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low);
		~ActorStateCachingSystem();
		virtual void OnInit() override;
		virtual void OnUpdate(Time) override;
		virtual void OnShutdown() override;
	};
}
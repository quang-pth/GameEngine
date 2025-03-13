#pragma once

#include"Core/Type/RTTI.h"
#include"ECS/ISystem.h"
#include<glm/glm.hpp>

namespace VIEngine {
	class VI_API DebugDrawSystem : public ECS::System<DebugDrawSystem> {
	public:
		DECLARE_RTTI
	public:
        DebugDrawSystem();
        DebugDrawSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low);
		~DebugDrawSystem();
        VI_FORCE_INLINE void SetQuadColor(const glm::vec3& color) { mQuadColor = color; }
		virtual void OnInit() override;
		virtual void OnUpdate(Time) override;
		virtual void OnShutdown() override;
    private:
        glm::vec3 mQuadColor = glm::vec3(1.0f);
	};
}
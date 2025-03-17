#pragma once

#include"Core/Type/RTTI.h"
#include"ECS/ISystem.h"
#include<glm/glm.hpp>
#include<box2d/box2d.h>

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
		void SetPhysicWorldID(b2WorldId id) { mWorldID = id; }
		const glm::vec3& GetQuadColor() const { return mQuadColor; }
    private:
        glm::vec3 mQuadColor = glm::vec3(1.0f);
		b2WorldId mWorldID;
		b2DebugDraw mPhysicWorldDebugDraw;
	};
}

#pragma once

#include"Core/Type/RTTI.h"
#include"ECS/ISystem.h"
#include<box2d/box2d.h>

namespace VIEngine {
    enum class EBodyType {
        STATIC,
        DYNAMIC,
        KINEMATIC
    };

	enum class EShapeType {
		CIRCLE,
		CAPSULE,
		SEGMENT,
		POLYGON,
		CHAIN_SEGMENT
	};

	float PixelToWorld(float pixels);
	float WorldToPixel(float meters);

	class VI_API PhysicSystem : public ECS::System<PhysicSystem> {
	public:
		DECLARE_RTTI
	public:
        PhysicSystem() = default;
		PhysicSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low);
		~PhysicSystem();
		virtual void OnInit() override;
		virtual void OnShutdown() override;
		virtual void OnStart() override;
		virtual void OnUpdate(Time) override;
		virtual void OnDestroyed() override;
 		VI_FORCE_INLINE b2WorldId GetWorldID() const { return mWorldID; }
    private:
        b2WorldDef mWorldDef;
        b2WorldId mWorldID;
	};
}
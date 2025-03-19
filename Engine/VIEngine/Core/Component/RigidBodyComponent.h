#pragma once

#include"pch.h"
#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"
#include"Core/System/PhysicSystem.h"
#include<box2d/box2d.h>

namespace VIEngine {
    class VI_API RigidBodyComponent : public ECS::Component<RigidBodyComponent, Actor> {
    public:
        DECLARE_RTTI
    public:
        RigidBodyComponent();
        ~RigidBodyComponent();
        VI_FORCE_INLINE void SetBodyID(b2BodyId bodyID) { mBodyID = bodyID; }
        VI_FORCE_INLINE b2BodyId GetBodyID() const { return mBodyID; }
        VI_FORCE_INLINE void SetBodyType(EBodyType body) { mBodyType = body; }
        VI_FORCE_INLINE EBodyType GetBodyType() const { return mBodyType; }
        VI_FORCE_INLINE void SetGravityScale(float scale) { mGravityScale = scale; }
        VI_FORCE_INLINE float GetGravityScale() const { return mGravityScale; }
        VI_FORCE_INLINE void SetLinearDamping(float damping) { mLinearDamping = damping; }
        VI_FORCE_INLINE float GetLinearDamping() const { return mLinearDamping; }
        VI_FORCE_INLINE void SetFixedRotation(bool fixedRotation) { mFixedRotation = fixedRotation; }
        VI_FORCE_INLINE float GetFixedRotation() const { return mFixedRotation; }
    private:
        b2BodyId mBodyID = b2_nullBodyId;
        EBodyType mBodyType = EBodyType::STATIC;
        float mGravityScale = 1.0f;
        float mLinearDamping = 1.0f;
        bool mFixedRotation = false;
    };
}
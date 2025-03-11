#pragma once

#include"pch.h"
#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"
#include"Core/System/PhysicSystem.h"
#include<box2d/box2d.h>

namespace VIEngine {
    class VI_API Box2DComponent : public ECS::Component<Box2DComponent, Actor> {
    public:
        DECLARE_RTTI
    public:
        Box2DComponent();
        ~Box2DComponent();
        VI_FORCE_INLINE void SetWidth(float width) { mWidth = width; }
        VI_FORCE_INLINE float GetWidth() const { return mWidth; }
        VI_FORCE_INLINE void SetHeight(float height) { mHeight = height; }
        VI_FORCE_INLINE float GetHeight() const { return mHeight; }
        VI_FORCE_INLINE void SetDensity(float density) { mDensity = density; }
        VI_FORCE_INLINE float GetDensity() const { return mDensity; }
        VI_FORCE_INLINE void SetFriction(float friction) { mFriction = friction; }
        VI_FORCE_INLINE float GetFriction() const { return mFriction; }
    private:
        b2BodyId mBodyID;
        float mWidth = 1.0f, mHeight = 1.0f;
        float mDensity = 1.0f;
        float mFriction = 0.3f;
    };
}
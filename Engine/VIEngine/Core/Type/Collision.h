#pragma once

#include"pch.h"
#include<glm/glm.hpp>

namespace VIEngine
{
    constexpr uint8_t MAX_CONTACT_POINTS = 2;

    struct ContactPoint {
        glm::vec2 WorldPosition;
        glm::vec2 AnchorA;
        glm::vec2 AnchorB;
        float Seperation;
        float NormalImpulse;
        float TangentImpulse;
        float MaxNormalImpulse;
        float NormalVelocity;
        uint16_t ID;
        bool Persisted;
    };

    struct Collision {
        glm::vec2 Normal;
        float RollingImpulse;
        uint8_t ContactCount;
        ContactPoint ContactPoints[MAX_CONTACT_POINTS];
        class RigidBodyComponent* CollideBody;
    };
} // namespace VIEngine

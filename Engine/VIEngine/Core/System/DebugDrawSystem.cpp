#include"DebugDrawSystem.h"
#include"PhysicSystem.h"
#include"Core/Component/RigidBodyComponent.h"
#include"Renderer/Renderer.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(DebugDrawSystem)

    DebugDrawSystem::DebugDrawSystem() {

    } 
    
    DebugDrawSystem::DebugDrawSystem(ECS::SystemID id, ECS::ESystemPriority priority)
        : ECS::System<DebugDrawSystem>(id, priority)
    {

    }
    
    DebugDrawSystem::~DebugDrawSystem() {

    }

    void DebugDrawSystem::OnInit() {

    }

    void DebugDrawSystem::OnUpdate(Time time) {
        for (RigidBodyComponent* rigidBody : mCoordinator->GetComponentArray<RigidBodyComponent>()) {
            b2AABB aabb = b2Body_ComputeAABB(rigidBody->GetBodyID());
            Renderer::DrawQuad(
                WorldToPixel(aabb.lowerBound.x), 
                WorldToPixel(-aabb.lowerBound.y), 
                WorldToPixel(aabb.upperBound.x), 
                WorldToPixel(-aabb.upperBound.y), 
                mQuadColor
            );
            // CORE_LOG_DEBUG("Min: {0}, {1}. Max: {2}, {3}", 
            //     WorldToPixel(aabb.lowerBound.x), 
            //     WorldToPixel(-aabb.lowerBound.y), 
            //     WorldToPixel(aabb.upperBound.x), 
            //     WorldToPixel(-aabb.upperBound.y)
            // );
        }
    }

    void DebugDrawSystem::OnShutdown() {

    }
} // namespace VIEngine

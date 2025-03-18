#include"DebugDrawSystem.h"
#include"PhysicSystem.h"
#include"Core/Component/RigidBodyComponent.h"
#include"Core/Component/Box2DComponent.h"
#include"Renderer/Renderer.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(DebugDrawSystem)
    
    glm::vec3 HexToRGB(const b2HexColor& hexColor) {
        glm::vec3 rgbColor;

        rgbColor.r = ((hexColor >> 16) & 0xFF) / 255.0f;
        rgbColor.g = ((hexColor >> 8) & 0xFF) / 255.0f;
        rgbColor.b = (hexColor & 0xFF) / 255.0f;

        return rgbColor;
    }

	void VIDrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context) {
        std::vector<glm::vec3> points;
        points.reserve(vertexCount);

        for (int i = 0; i < vertexCount; ++i) {
            points.push_back({WorldToPixel(vertices[i].x), WorldToPixel(vertices[i].y), 0.0f});
        }

        Renderer::DrawPolygon(points.data(), points.size(), HexToRGB(color));
    }

    DebugDrawSystem::DebugDrawSystem() {

    } 
    
    DebugDrawSystem::DebugDrawSystem(ECS::SystemID id, ECS::ESystemPriority priority)
        : ECS::System<DebugDrawSystem>(id, priority)
    {

    }
    
    DebugDrawSystem::~DebugDrawSystem() {

    }

    void DebugDrawSystem::OnInit() {
       mPhysicWorldDebugDraw = b2DefaultDebugDraw();
       mPhysicWorldDebugDraw.DrawPolygon = VIDrawPolygon;
       mPhysicWorldDebugDraw.drawAABBs = true;
       mPhysicWorldDebugDraw.context = this;
    }

    void DebugDrawSystem::OnUpdate(Time time) {
        if (b2World_IsValid(mWorldID)) {
            b2World_Draw(mWorldID, &mPhysicWorldDebugDraw);
        }

        // for (RigidBodyComponent* rigidBody : mCoordinator->GetComponentArray<RigidBodyComponent>()) {
        //     // b2AABB aabb = b2Body_ComputeAABB(rigidBody->GetBodyID());
  
        //     // Renderer::DrawQuad(
        //     //     WorldToPixel(aabb.lowerBound.x), 
        //     //     WorldToPixel(aabb.lowerBound.y), 
        //     //     WorldToPixel(aabb.upperBound.x), 
        //     //     WorldToPixel(aabb.upperBound.y),
        //     //     mQuadColor
        //     // );
        //     // CORE_LOG_DEBUG("Min: {0}, {1}. Max: {2}, {3}", 
        //     //     WorldToPixel(aabb.lowerBound.x), 
        //     //     WorldToPixel(-aabb.lowerBound.y), 
        //     //     WorldToPixel(aabb.upperBound.x), 
        //     //     WorldToPixel(-aabb.upperBound.y)
        //     // );
            
        //     // CORE_LOG_DEBUG("Position: {0} {1}", 
        //     //     WorldToPixel(b2Body_GetPosition(rigidBody->GetBodyID()).x), 
        //     //     WorldToPixel(b2Body_GetPosition(rigidBody->GetBodyID()).y)
        //     // );
        // }
    }

    void DebugDrawSystem::OnShutdown() {

    }
} // namespace VIEngine

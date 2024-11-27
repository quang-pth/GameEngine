#include"DirtySpriteValidationSystem.h"
#include"Core/Component/StateCachingComponent.h"
#include"Core/Component/TransformComponent.h"
#include"Core/Component/AnimatorComponent.h"
#include"Core/Component/SpriteComponent.h"
#include"Resource/Sprite.h"
#include"ECS/Coordinator.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(DirtySpriteValidationSystem)
    
    DirtySpriteValidationSystem::DirtySpriteValidationSystem() {

    }

	DirtySpriteValidationSystem::DirtySpriteValidationSystem(ECS::SystemID id, ECS::ESystemPriority priority) : ECS::System<DirtySpriteValidationSystem>(id, priority) {

    }

    DirtySpriteValidationSystem::~DirtySpriteValidationSystem() {

    }

    void DirtySpriteValidationSystem::OnInit() {

    }

    void DirtySpriteValidationSystem::OnUpdate(Time time) {
        for (AnimatorComponent* animator : mCoordinator->GetComponentArray<AnimatorComponent>()) { 
            TransformComponent& transformComponent = animator->GetOwner().GetComponent<TransformComponent>();
            StateCachingComponent& stateCachingComponent = animator->GetOwner().GetComponent<StateCachingComponent>();
            bool diffPosition = transformComponent.GetPosition() != stateCachingComponent.GetPosition();
            bool diffScale = transformComponent.GetScale() != stateCachingComponent.GetScale();
            bool diffRotation = transformComponent.GetRotation() != stateCachingComponent.GetRotation();

            animator->GetActiveAnimation()->CurrentFrame()->SetIsDirty(diffPosition || diffScale || diffRotation);
        }

        for (SpriteComponent* spriteComponent : mCoordinator->GetComponentArray<SpriteComponent>()) {
            TransformComponent& transformComponent = spriteComponent->GetOwner().GetComponent<TransformComponent>();
            StateCachingComponent& stateCachingComponent = spriteComponent->GetOwner().GetComponent<StateCachingComponent>();
            bool diffPosition = transformComponent.GetPosition() != stateCachingComponent.GetPosition();
            bool diffScale = transformComponent.GetScale() != stateCachingComponent.GetScale();
            bool diffRotation = transformComponent.GetRotation() != stateCachingComponent.GetRotation();

            spriteComponent->GetSprite()->SetIsDirty(diffPosition || diffScale || diffRotation);
        }
    }

    void DirtySpriteValidationSystem::OnShutdown() {

    }
}
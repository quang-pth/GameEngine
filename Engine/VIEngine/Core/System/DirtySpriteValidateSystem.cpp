#include"DirtySpriteValidateSystem.h"
#include"Core/Component/DirtySpriteComponent.h"
#include"Core/Component/TransformComponent.h"
#include"ECS/Coordinator.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(DirtySpriteValidateSystem)
    
    DirtySpriteValidateSystem::DirtySpriteValidateSystem() {

    }

	DirtySpriteValidateSystem::DirtySpriteValidateSystem(ECS::SystemID id, ECS::ESystemPriority priority) : ECS::System<DirtySpriteValidateSystem>(id, priority) {

    }

    DirtySpriteValidateSystem::~DirtySpriteValidateSystem() {

    }

    void DirtySpriteValidateSystem::OnInit() {

    }

    void DirtySpriteValidateSystem::OnUpdate(Time time) {
        for (DirtySpriteComponent* dirtySpriteComponent : mCoordinator->GetComponentArray<DirtySpriteComponent>()) {
            TransformComponent& transformComponent = dirtySpriteComponent->GetOwner().GetComponent<TransformComponent>();
            bool diffPosition = transformComponent.GetPosition() != dirtySpriteComponent->GetPosition();
            bool diffScale = transformComponent.GetScale() != dirtySpriteComponent->GetScale();
            bool diffRotation = transformComponent.GetRotation() != dirtySpriteComponent->GetRotation();
            dirtySpriteComponent->SetIsDirty(diffPosition || diffScale || diffRotation);
        }
    }

    void DirtySpriteValidateSystem::OnShutdown() {

    }
}
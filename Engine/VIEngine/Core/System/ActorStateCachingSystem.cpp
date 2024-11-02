#include"ActorStateCachingSystem.h"
#include"Core/Component/StateCachingComponent.h"
#include"Core/Component/TransformComponent.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(ActorStateCachingSystem)

    ActorStateCachingSystem::ActorStateCachingSystem() {

    }

    ActorStateCachingSystem::ActorStateCachingSystem(ECS::SystemID id, ECS::ESystemPriority priority) 
        : ECS::System<ActorStateCachingSystem>(id, priority) 
    {

    }

    ActorStateCachingSystem::~ActorStateCachingSystem() {

    }

    void ActorStateCachingSystem::OnInit() {

    }

    void ActorStateCachingSystem::OnUpdate(Time time) {
        for (StateCachingComponent* stateCachingComponent : mCoordinator->GetComponentArray<StateCachingComponent>()) {
            TransformComponent& transform = stateCachingComponent->GetOwner().GetComponent<TransformComponent>();
            stateCachingComponent->SetPosition(transform.GetPosition());
            stateCachingComponent->SetScale(transform.GetScale());
            stateCachingComponent->SetRotation(transform.GetRotation());
        }
    }

    void ActorStateCachingSystem::OnShutdown() {

    }
}
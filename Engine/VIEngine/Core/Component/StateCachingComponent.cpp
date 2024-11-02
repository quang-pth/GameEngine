#include"StateCachingComponent.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(StateCachingComponent)

    StateCachingComponent::StateCachingComponent() 
        : mPreviousPosition(0.0f), mPreviousScale(1.0f), mPreviousRotation(0.0f)
    {
    }

    StateCachingComponent::~StateCachingComponent() {

    }
}
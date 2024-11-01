#include"DirtySpriteComponent.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(DirtySpriteComponent)

    DirtySpriteComponent::DirtySpriteComponent() 
        : mPreviousPosition(0.0f), mPreviousScale(1.0f), mPreviousRotation(0.0f), mIsDirty(false)
    {
    }

    DirtySpriteComponent::~DirtySpriteComponent() {

    }
}
#pragma once

#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"
#include<glm/glm.hpp>

namespace VIEngine {
    class VI_API StateCachingComponent : public ECS::Component<StateCachingComponent, Actor> {
        public:
            DECLARE_RTTI
        public:
            StateCachingComponent();
            ~StateCachingComponent();
            VI_FORCE_INLINE const glm::vec3& GetPosition() const { return mPreviousPosition; }
            VI_FORCE_INLINE void SetPosition(const glm::vec3& position) { mPreviousPosition = position; }
            VI_FORCE_INLINE const glm::vec3& GetScale() const { return mPreviousScale; }
            VI_FORCE_INLINE void SetScale(const glm::vec3& scale) { mPreviousScale = scale; }
            VI_FORCE_INLINE const glm::vec3& GetRotation() const { return mPreviousRotation; }
            VI_FORCE_INLINE void SetRotation(const glm::vec3& rotation) { mPreviousRotation = rotation; }
        private:
            glm::vec3 mPreviousPosition;           
            glm::vec3 mPreviousScale;           
            glm::vec3 mPreviousRotation;           
    };
}
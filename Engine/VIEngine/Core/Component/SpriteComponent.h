#pragma once

#include"pch.h"
#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"
#include<glm/glm.hpp>

namespace VIEngine {
    class VI_API SpriteComponent : public ECS::Component<SpriteComponent, Actor> {
    public:
        DECLARE_RTTI
    public:
        SpriteComponent();
        ~SpriteComponent();
        void SetSprite(const std::string& filepath);
        VI_FORCE_INLINE void SetSprite(class Sprite* sprite) { mSprite = sprite; }
        VI_FORCE_INLINE Sprite* GetSprite() const { return mSprite; }
        void SetColor(const glm::vec4& color);
        VI_FORCE_INLINE const glm::vec4& GetColor() const;
        VI_FORCE_INLINE bool GetFlipVertical() const { return mFlipVertical; }
        VI_FORCE_INLINE void SetFlipVertical(bool flipVertical) { mFlipVertical = flipVertical; }
        VI_FORCE_INLINE bool GetFlipHorizontal() const { return mFlipHorizontal; }
        VI_FORCE_INLINE void SetFlipHorizontal(bool flipHorizontal) { mFlipHorizontal = flipHorizontal; }
    private:
        class Sprite* mSprite;
        bool mFlipVertical, mFlipHorizontal;
    };
}
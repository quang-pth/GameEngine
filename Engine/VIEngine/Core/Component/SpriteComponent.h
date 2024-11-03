#pragma once

#include"pch.h"
#include"Resource/Sprite.h"
#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"

namespace VIEngine {
    class VI_API SpriteComponent : public ECS::Component<SpriteComponent, Actor> {
    public:
        DECLARE_RTTI
    public:
        SpriteComponent();
        ~SpriteComponent();
    private:
        Sprite mSprite;
    };
}
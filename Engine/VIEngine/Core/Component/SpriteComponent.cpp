#include"SpriteComponent.h"
#include"Resource/Sprite.h"

namespace VIEngine {
    DEFINE_RTTI_NO_PARENT(SpriteComponent)

    SpriteComponent::SpriteComponent() {

    }

    SpriteComponent::~SpriteComponent() {

    }

    void SpriteComponent::SetSprite(const std::string& filepath) {
        mSprite = Sprite::Create(filepath);
    }

    void SpriteComponent::SetColor(const glm::vec4& color) {
        mSprite->SetColor(color);
    }

    const glm::vec4& SpriteComponent::GetColor() const {
        return mSprite->GetColor();
    }
}
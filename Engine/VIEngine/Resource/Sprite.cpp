#include"Sprite.h"
#include"Texture2D.h"
#include"ResourceManager.h"

namespace VIEngine {
	Sprite* Sprite::Create(const std::string& filepath) {
		return ResourceManager::Get().NewSprite(filepath);
	}

    Sprite::Sprite(const std::string& filepath) : mFilePath(filepath), mName(filepath) {
        mTexture = Texture2D::Create(filepath);
    }

    Sprite::~Sprite() {
    }

	void Sprite::Release() {
        mTexture->Release();
	}
}
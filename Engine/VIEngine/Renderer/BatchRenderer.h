#pragma once

#include"pch.h"
#include"Core/Component/TransformComponent.h"
#include"RenderBatch.h"

namespace VIEngine {
	constexpr uint8_t MAX_TEXTURE_UNITS = 32;

	class VI_API BatchRenderer {
	public:
		BatchRenderer();
		~BatchRenderer();

		void Submit();
		void Clear();
		void InsertBatch(const SpriteBatch& spriteBatch);
	private:
		std::vector<RenderBatch> mRenderBatches;
		class Shader* mShader;
		std::array<class Texture2D*, MAX_TEXTURE_UNITS> mTextures;
		int8_t mTextureCount;
	};
}
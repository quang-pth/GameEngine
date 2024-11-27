#pragma once

#include"pch.h"
#include"Core/Component/TransformComponent.h"
#include"Resource/VertexBuffer.h"
#include"Resource/VertexFormat.h"

namespace VIEngine {
    constexpr uint8_t MAX_BATCH_SIZE = 50;
	constexpr uint8_t MAX_TEXTURE_UNITS = 32;

	struct SpriteBatch {
		Transform SpriteTransform;
		class Sprite* SpriteContext;
		bool FlipVertical = false;
		bool FlipHorizontal = false;
		uint8_t SampleTextureID;
		float Depth;
	};

	class VI_API RenderBatch {
		public:
			RenderBatch();
			~RenderBatch();
			void Release();
			void SubmitVerticesAndIndices();
			bool HasSlot() const;
			void Insert(const SpriteBatch&);
			int32_t InsertTexture(class Texture2D* texture);
			class Texture2D* GetTexture(uint32_t textureSlot) const;
			VI_FORCE_INLINE int32_t GetTextureSlots() const { return mCurrentTextureIdx; }
			VI_FORCE_INLINE bool HasTextureSlot() const { return mCurrentTextureIdx < MAX_TEXTURE_UNITS; }
			int32_t GetTextureSlot(uint32_t textureID) const;
			VI_FORCE_INLINE class VertexArray* GetVertexArray() const { return mVertexArray; }
		private:
			std::array<BatchedVertex, MAX_BATCH_SIZE * 4> mVertices;
			std::array<uint32_t, MAX_BATCH_SIZE * 6> mIndices;
			std::array<class Texture2D*, MAX_TEXTURE_UNITS> mTextures;
			uint32_t mCurrentTextureIdx = 0;
			int mBatchCount;
			class VertexArray* mVertexArray;
			VertexFormat mVertexFormat;
	};

}
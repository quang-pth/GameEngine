#pragma once

#include"pch.h"
#include"Core/Component/TransformComponent.h"
#include"Resource/VertexBuffer.h"

namespace VIEngine {
    constexpr uint8_t MAX_BATCH_SIZE = 50;
	constexpr uint8_t MAX_TEXTURE_UNITS = 16;

	class VI_API RenderBatch {
		public:
			RenderBatch();
			~RenderBatch();
			void Submit();
			bool HasSlot() const;
			void Insert(const Transform& transform, class Vertex* vertices, uint32_t* indices, class Texture2D* texture, bool flipVertical, bool flipHorizontal);
		private:
			std::array<BatchedVertex, MAX_BATCH_SIZE * 4> mVertices;
			std::array<uint32_t, MAX_BATCH_SIZE * 6> mIndices;
			std::array<class Texture2D*, MAX_TEXTURE_UNITS> mTextures;
			int8_t mTextureCount;
			int8_t mBatchCount;
			class VertexArray* mVertexArray;
            class Shader* mShader;
	};

}
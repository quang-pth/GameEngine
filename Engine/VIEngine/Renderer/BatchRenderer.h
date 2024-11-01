#pragma once

#include"pch.h"
#include"Core/Component/TransformComponent.h"
#include"Resource/VertexBuffer.h"

namespace VIEngine {
	constexpr uint8_t MAX_BATCH_SIZE = 50;
	constexpr uint8_t MAX_TEXTURE_UNITS = 16;

	class VI_API BatchRenderer {
	public:
		BatchRenderer();
		~BatchRenderer();

		void Submit();
		void Clear();
		void InsertBatch(const Transform& transform, Vertex* vertices, uint32_t* indices, class Texture2D*, bool flipVertical, bool flipHorizontal);
		bool HasSlot() const;
	protected:
		std::array<BatchedVertex, MAX_BATCH_SIZE> mVertices;
		std::array<uint32_t, MAX_BATCH_SIZE * 6> mIndices;
		std::array<class Texture2D*, MAX_BATCH_SIZE> mTextures;
		uint8_t mBatchIdx;
		uint8_t mTextureIdx;
		class VertexArray* mVertexArray;
		class Shader* mShader;
	};
}
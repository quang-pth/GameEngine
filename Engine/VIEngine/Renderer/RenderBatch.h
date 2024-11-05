#pragma once

#include"pch.h"
#include"Core/Component/TransformComponent.h"
#include"Resource/VertexBuffer.h"
#include"Resource/VertexFormat.h"

namespace VIEngine {
    constexpr uint8_t MAX_BATCH_SIZE = 50;

	class VI_API RenderBatch {
		public:
			RenderBatch();
			~RenderBatch();
			void SubmitVertexAndIndexBuffer();
			bool HasSlot() const;
			void Insert(const Transform& transform, class Sprite* sprite);
		private:
			std::array<BatchedVertex, MAX_BATCH_SIZE * 4> mVertices;
			std::array<uint32_t, MAX_BATCH_SIZE * 6> mIndices;
			int8_t mBatchCount;
			class VertexArray* mVertexArray;
            class Shader* mShader;
			VertexFormat mVertexFormat;
	};

}
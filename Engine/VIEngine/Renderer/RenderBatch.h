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
			void SubmitVerticesAndIndices();
			bool HasSlot() const;
			void Insert(const Transform& transform, class Sprite* sprite);
			VI_FORCE_INLINE class VertexArray* GetVertexArray() const { return mVertexArray; }
		private:
			std::array<BatchedVertex, MAX_BATCH_SIZE * 4> mVertices;
			std::array<uint32_t, MAX_BATCH_SIZE * 6> mIndices;
			int mBatchCount;
			class VertexArray* mVertexArray;
            class Shader* mShader;
			VertexFormat mVertexFormat;
	};

}
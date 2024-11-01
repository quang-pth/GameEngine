#pragma once

#include"pch.h"
#include"Core/Component/TransformComponent.h"
#include"Resource/VertexBuffer.h"
#include"RenderBatch.h"

namespace VIEngine {
	class VI_API BatchRenderer {
	public:
		BatchRenderer();
		~BatchRenderer();

		void Submit();
		void Clear();
		void InsertBatch(const Transform& transform, Vertex* vertices, uint32_t* indices, class Texture2D*, bool flipVertical, bool flipHorizontal);
	private:
		std::vector<RenderBatch> mRenderBatches;
	};
}
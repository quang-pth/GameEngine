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
		void InsertBatch(const Transform& transform, class Sprite* sprite);
	private:
		std::vector<RenderBatch> mRenderBatches;
	};
}
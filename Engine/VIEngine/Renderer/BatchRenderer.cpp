#include"BatchRenderer.h"
#include"Resource/Texture2D.h"

namespace VIEngine {
	BatchRenderer::BatchRenderer() : mRenderBatches() {
		mRenderBatches.push_back(RenderBatch());
	}

	BatchRenderer::~BatchRenderer() {

	}

	void BatchRenderer::Submit() {
		for (auto& renderBatch : mRenderBatches) {
			renderBatch.Submit();
		}
	}
	
	void BatchRenderer::Clear() {
		mRenderBatches.clear();
		mRenderBatches.push_back(RenderBatch());
	}

	void BatchRenderer::InsertBatch(const Transform& transform, Vertex* vertices, uint32_t* indices, Texture2D* texture, bool flipVertical, bool flipHorizontal)
	{
		RenderBatch* batch = &mRenderBatches.back();
		if (!batch->HasSlot()) {
			mRenderBatches.push_back(RenderBatch());
			batch = &mRenderBatches.back();
		}

		batch->Insert(transform, vertices, indices, texture, flipVertical, flipHorizontal);
	}
}
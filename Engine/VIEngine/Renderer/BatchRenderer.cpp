#include"BatchRenderer.h"
#include"Resource/Texture2D.h"
#include"Resource/Sprite.h"

namespace VIEngine {
	BatchRenderer::BatchRenderer() : mRenderBatches() {
		mRenderBatches.emplace_back();
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
		mRenderBatches.emplace_back();
	}

	void BatchRenderer::InsertBatch(const Transform& transform, Sprite* sprite)
	{
		RenderBatch* batch = &mRenderBatches.back();
		if (!batch->HasSlot()) {
			mRenderBatches.emplace_back();
			batch = &mRenderBatches.back();
		}

		// TODO: Cache not need update vertices and indicies data
		batch->Insert(transform, sprite);
	}
}
#pragma once

#include"pch.h"
#include"Core/Component/TransformComponent.h"
#include"RenderBatch.h"
#include"Memory/MemoryManager.h"

namespace VIEngine {
	class VI_API BatchRenderer {
	public:
		BatchRenderer();
		~BatchRenderer();

		void Begin();
		void End();
		void InsertBatch(const SpriteBatch& spriteBatch);
	private:
		void GenerateRenderBatches();
	private:
		std::multimap<float, SpriteBatch> mSpriteBatchesMap;
		std::vector<RenderBatch*> mRenderBatches;
		class Shader* mShader;
		MemoryManager mMemoryManager;
	};
}
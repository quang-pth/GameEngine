#include"BatchRenderer.h"
#include"Resource/Texture2D.h"
#include"Resource/Sprite.h"
#include"Resource/Shader.h"
#include"Resource/VertexArray.h"
#include"Resource/IndexBuffer.h"
#include"Renderer.h"
#include"Core/Application.h"
#include"Renderer/Camera/Camera.h"
#include<glm/gtc/matrix_transform.hpp>

namespace VIEngine {
	BatchRenderer::BatchRenderer() : mRenderBatches(), mMemoryManager(), mSpriteBatchesMap() {
		mShader = Shader::Create("Assets/Shader/render-batch.glsl");
	}

	BatchRenderer::~BatchRenderer() {

	}

	void BatchRenderer::Begin() {
		mRenderBatches.clear();
		mSpriteBatchesMap.clear();
	}
	
	void BatchRenderer::End() {
		GenerateRenderBatches();

		mShader->Bind();
		mShader->SetMatrix4("viewMatrix", mCamera->GetViewMatrix());
		mShader->SetMatrix4("projectionMatrix", mCamera->GetProjectionMatrix());

		for (auto& renderBatch : mRenderBatches) {
			if (renderBatch->GetBatchCount() == 0) {
				continue;
			}

			uint32_t textureSlots = renderBatch->GetTextureSlots();

			for (int8_t i = 0; i < textureSlots; i++) {
				Renderer::ActivateTexture(i);
				Renderer::BindTexture2D(renderBatch->GetTexture(i)->GetID());
				mShader->SetInt("textures[" + std::to_string(i) + "]", i);
			}

			renderBatch->SubmitVerticesAndIndices();
			Renderer::DrawIndexed(renderBatch->GetVertexArray()->GetIndexBuffer()->GetNums());
			renderBatch->Release();
		}
	}

	void BatchRenderer::InsertBatch(const SpriteBatch& spriteBatch)
	{
		mSpriteBatchesMap.insert({ spriteBatch.Depth, spriteBatch });
	}

	void BatchRenderer::GenerateRenderBatches() {
		mRenderBatches.emplace_back(mMemoryManager.NewPerFrame<RenderBatch>());
		RenderBatch* renderBatch = mRenderBatches.back();

		for (auto& [_, spriteBatch] : mSpriteBatchesMap) {
			if (!renderBatch->HasSlot()) {
				mRenderBatches.emplace_back(mMemoryManager.NewPerFrame<RenderBatch>());
				renderBatch = mRenderBatches.back();
			}

			Texture2D* texture = spriteBatch.SpriteContext->GetTexture();

			int8_t selectedTextureID = renderBatch->GetTextureSlot(texture->GetID());

			// Render Batch does not contain the current bound texture
			if (selectedTextureID == -1) {
				// Render Batch is full of texture slot before running out of batch capacity
				if (!renderBatch->HasTextureSlot()) {
					mRenderBatches.emplace_back();
					renderBatch = mRenderBatches.back();
				}

				selectedTextureID = renderBatch->InsertTexture(texture);
			}
			spriteBatch.SampleTextureID = selectedTextureID;

			// TODO: Cache not need update vertices and indicies data
			renderBatch->Insert(spriteBatch);
		}
	}
}
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
	BatchRenderer::BatchRenderer() : mRenderBatches(), mTextureCount(0), mTextures() {
		mShader = Shader::Create("Assets/Shader/render-batch.glsl");
	}

	BatchRenderer::~BatchRenderer() {

	}

	void BatchRenderer::Submit() {
		// TODO: Make camera configurable later
		static glm::mat4 projection = glm::ortho(0.0f, 20.0f, 20.0f, 0.0f, -1.0f, 10.f);
		static Camera camera = Camera(projection);
		camera.Update();	

		mShader->Bind();
		mShader->SetMatrix4("viewMatrix", camera.GetViewMatrix());
		mShader->SetMatrix4("projectionMatrix", projection);
		for (int8_t i = 0; i < mTextureCount; i++) {
			Renderer::ActivateTexture(i);
			Renderer::BindTexture2D(mTextures[i]->GetID());
			mShader->SetInt("textures[" + std::to_string(i) + "]", i);
		}

		for (auto& renderBatch : mRenderBatches) {
			renderBatch.SubmitVerticesAndIndices();
			Renderer::DrawIndexed(renderBatch.GetVertexArray()->GetIndexBuffer()->GetNums());
		}
	}
	
	void BatchRenderer::Clear() {
		mRenderBatches.clear();
		mTextureCount = 0;
	}

	void BatchRenderer::InsertBatch(const SpriteBatch& spriteBatch)
	{
		Texture2D* texture = spriteBatch.SpriteContext->GetTexture();
			
		int8_t selectedTextureID = -1;
		for (int8_t i = 0; i < mTextureCount; i++) {
			if (mTextures[i]->GetName() == texture->GetName()) {
				selectedTextureID = i;
				break;
			}
		}

		if (selectedTextureID == -1) {
			if (mTextureCount >= MAX_TEXTURE_UNITS) {
				Submit();
				Clear();
			}
			selectedTextureID = mTextureCount;
			mTextures[mTextureCount++] = texture;
		}
		spriteBatch.SpriteContext->SetSampleTextureID(selectedTextureID);

		if (!mRenderBatches.size()) {
			mRenderBatches.emplace_back();
		}

		RenderBatch* batch = &mRenderBatches.back();
		if (!batch->HasSlot()) {
			mRenderBatches.emplace_back();
			batch = &mRenderBatches.back();
		}

		// TODO: Cache not need update vertices and indicies data
		batch->Insert(spriteBatch);
	}
}
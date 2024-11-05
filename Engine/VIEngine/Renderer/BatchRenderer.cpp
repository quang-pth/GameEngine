#include"BatchRenderer.h"
#include"Resource/Texture2D.h"
#include"Resource/Sprite.h"
#include"Resource/Shader.h"
#include"Renderer.h"
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
		static glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 10.f);
		static Camera camera = Camera(projection);
		camera.Update();

		mShader->Bind();
		mShader->SetMatrix4("viewMatrix", camera.GetViewMatrix());
		mShader->SetMatrix4("projectionMatrix", projection);
		for (uint8_t i = 0; i < mTextureCount; i++) {
			Renderer::ActivateTexture(i);
			Renderer::BindTexture2D(mTextures[i]->GetID());
			mShader->SetInt("textures[" + std::to_string(i) + "]", i);
		}

		for (auto& renderBatch : mRenderBatches) {
			renderBatch.SubmitVertexAndIndexBuffer();
		}
	}
	
	void BatchRenderer::Clear() {
		mRenderBatches.clear();
		mRenderBatches.emplace_back();
		mTextureCount = 0;
	}

	void BatchRenderer::InsertBatch(const Transform& transform, Sprite* sprite)
	{
		Texture2D* texture = sprite->GetTexture();

		int8_t selectedTextureID = -1;
		for (int8_t i = 0; i < mTextureCount; i++) {
			if (mTextures[i]->GetName() == texture->GetName()) {
				selectedTextureID = i;
				break;
			}
		}

		if (selectedTextureID == -1) {
			selectedTextureID = mTextureCount;
			mTextures[mTextureCount++] = texture;
		}
		sprite->SetSampleTextureID(selectedTextureID);

		RenderBatch* batch = &mRenderBatches.back();
		if (!batch->HasSlot()) {
			mRenderBatches.emplace_back();
			batch = &mRenderBatches.back();
		}

		// TODO: Cache not need update vertices and indicies data
		batch->Insert(transform, sprite);
	}
}
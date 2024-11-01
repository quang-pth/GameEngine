#include"BatchRenderer.h"
#include"Renderer/Renderer.h"
#include"Renderer/RenderCommand.h"
#include"Resource/VertexArray.h"
#include"Resource/IndexBuffer.h"
#include"Resource/Texture2D.h"
#include"Resource/Shader.h"

#include"Renderer/Camera/Camera.h"
#include<glm/gtc/matrix_transform.hpp>

namespace VIEngine {
	BatchRenderer::BatchRenderer() : mTextures(), mBatchIdx(0), mVertexArray(), mVertices(), mIndices(), mTextureIdx(0) {
		mShader = Shader::Create("Assets/Shader/render-batch.glsl");
		mVertexArray = VertexArray::Create(true);
	}

	BatchRenderer::~BatchRenderer() {

	}

	void BatchRenderer::Submit() {
		static glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 10.f);
		static Camera camera = Camera(projection);
		camera.Update();

		mVertexArray->SetVertexBuffer(mVertices.data(), sizeof(BatchedVertex) * mBatchIdx * 4);
		mVertexArray->SetIndexBuffer(mIndices.data(), sizeof(uint32_t) * mBatchIdx * 6, mBatchIdx * 6);
		
		mShader->Bind();
		mShader->SetMatrix4("viewMatrix", camera.GetViewMatrix());
		mShader->SetMatrix4("projectionMatrix", projection);
		for (uint8_t i = 0; i < mTextureIdx; i++) {
			Renderer::ActivateTexture(i);
			Renderer::BindTexture2D(mTextures[i]->GetID());
			mShader->SetInt("textures[" + std::to_string(i) + "]", i);
		}
		mVertexArray->Bind();
		Renderer::DrawIndexed(mVertexArray->GetIndexBuffer()->GetNums());
	}
	
	void BatchRenderer::Clear() {
		mBatchIdx = 0;
		mTextureIdx = 0;
	}

	void BatchRenderer::InsertBatch(const Transform& transform, Vertex* vertices, uint32_t* indices, Texture2D* texture, bool flipVertical, bool flipHorizontal)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, transform.Scale);
		model = glm::translate(model, transform.Position);
		// TODO: Add rotation later
		//model = glm::rotate(model, transform.Rotation.y, glm::vec3());

		for (uint8_t i = 0; i < 4; i++) {
			mVertices[mBatchIdx * 4 + i].Position = glm::vec3(model * glm::vec4(vertices[i].Position, 1.0f));
			mVertices[mBatchIdx * 4 + i].TexCoords = vertices[i].TexCoords;
			mVertices[mBatchIdx * 4 + i].TextureID = mTextureIdx;
			mVertices[mBatchIdx * 4 + i].FlipVertical = (int)flipVertical;
			mVertices[mBatchIdx * 4 + i].FlipHorizontal = (int)flipHorizontal;
		}

		for (uint8_t i = 0; i < 6; i++) {
			mIndices[mBatchIdx * 6 + i] = indices[i] + mBatchIdx * 4;
		}

		bool existedTexture = false;
		for (uint8_t i = 0; i < mTextureIdx; i++) {
			if (mTextures[i]->GetName() == texture->GetName()) {
				existedTexture = true;
				break;
			}

		}
		if (!existedTexture) {
			mTextures[mTextureIdx++] = texture;
		}

		mBatchIdx++;
	}

	bool BatchRenderer::HasSlot() const
	{
		return mBatchIdx < MAX_BATCH_SIZE && mTextureIdx < MAX_TEXTURE_UNITS;
	}
}
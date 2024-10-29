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
		mVertexArray = VertexArray::Create();
	}

	BatchRenderer::~BatchRenderer() {

	}

	void BatchRenderer::Submit() {
		static glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 10.f);
		static Camera camera = Camera(projection);
		camera.Update();

		mVertexArray->SetVertexBuffer(mVertices.data(), sizeof(Vertex) * mBatchIdx * 4);
		mVertexArray->SetIndexBuffer(mIndices.data(), sizeof(uint32_t) * mBatchIdx * 6, mBatchIdx * 6);
		
		mShader->Bind();
		mShader->SetMatrix4("viewMatrix", camera.GetViewMatrix());
		mShader->SetMatrix4("projectionMatrix", projection);
		mVertexArray->Bind();
		Renderer::Submit([this]() {
			for (uint8_t i = 0; i < mTextureIdx; i++) {
				RenderCommand::ActivateTexture(i);
				RenderCommand::BindTexture2D(mTextures[i]);
			}
			RenderCommand::DrawIndexed(mVertexArray->GetIndexBuffer()->GetNums());
		});
	}
	
	void BatchRenderer::Clear() {
		mBatchIdx = 0;
		mTextureIdx = 0;
	}

	void BatchRenderer::InsertBatch(const Transform& transform, Vertex* vertices, uint32_t* indices, Texture2D* texture)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, transform.Scale);
		model = glm::translate(model, transform.Position);
		// TODO: Add rotation later
		//model = glm::rotate(model, transform.Rotation.y, glm::vec3());

		// TODO: Fix 
		for (uint8_t i = 0; i < 4; i++) {
			mVertices[mBatchIdx + i].Position = glm::vec3(model * glm::vec4(vertices[i].Position, 1.0f));
			mVertices[mBatchIdx + i].TexCoords = vertices[i].TexCoords;
			mVertices[mBatchIdx + i].Color = vertices[i].Color;
		}

		for (uint8_t i = 0; i < 6; i++) {
			mIndices[mBatchIdx + i] = indices[i] + mBatchIdx * 4;
		}
		
		// TODO: Init texture id before send it to batch renderer
		mTextures[mTextureIdx++] = texture->GetID();
		mBatchIdx++;
	}

	bool BatchRenderer::HasSlot() const
	{
		return mBatchIdx < MAX_BATCH_SIZE && mTextureIdx < MAX_TEXTURE_UNITS;
	}
}
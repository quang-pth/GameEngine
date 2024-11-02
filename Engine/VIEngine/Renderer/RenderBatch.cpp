#include"RenderBatch.h"
#include"Renderer/Renderer.h"
#include"Renderer/RenderCommand.h"
#include"Resource/VertexArray.h"
#include"Resource/IndexBuffer.h"
#include"Resource/Texture2D.h"
#include"Resource/Shader.h"
#include"Resource/Sprite.h"

#include"Renderer/Camera/Camera.h"
#include<glm/gtc/matrix_transform.hpp>

namespace VIEngine {
    RenderBatch::RenderBatch() : mTextureCount(0), mBatchCount(0), mVertices(), mIndices() {
		mShader = Shader::Create("Assets/Shader/render-batch.glsl");
		mVertexArray = VertexArray::Create(true);
    }

    RenderBatch::~RenderBatch() {
		mVertexArray->Release();
	}

    void RenderBatch::Submit() {
		// TODO: Make camera configurable later
        static glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 10.f);
		static Camera camera = Camera(projection);
		camera.Update();

		mVertexArray->SetVertexBuffer(mVertices.data(), sizeof(BatchedVertex) * mBatchCount * 4);
		mVertexArray->SetIndexBuffer(mIndices.data(), sizeof(uint32_t) * mBatchCount * 6, mBatchCount* 6);
		
		mShader->Bind();
		mShader->SetMatrix4("viewMatrix", camera.GetViewMatrix());
		mShader->SetMatrix4("projectionMatrix", projection);
		for (uint8_t i = 0; i < mTextureCount; i++) {
			Renderer::ActivateTexture(i);
			Renderer::BindTexture2D(mTextures[i]->GetID());
			mShader->SetInt("textures[" + std::to_string(i) + "]", i);
		}
		mVertexArray->Bind();
		Renderer::DrawIndexed(mVertexArray->GetIndexBuffer()->GetNums());
    }

    bool RenderBatch::HasSlot() const {
        return mBatchCount < MAX_BATCH_SIZE && mTextureCount < MAX_TEXTURE_UNITS;
    }

    void RenderBatch::Insert(const Transform& transform, Sprite* sprite) 
	{
		Texture2D* texture = sprite->GetTexture();
		VertexBuffer* vertexBuffer = sprite->GetVertexArray()->GetVertexBuffer();
		IndexBuffer* indexBuffer = sprite->GetVertexArray()->GetIndexBuffer();

		int8_t selectedTextureID = mTextureCount - 1;
		for (int8_t i = 0; i < mTextureCount; i++) {
			if (mTextures[i]->GetName() == texture->GetName()) {
				selectedTextureID = i;
				break;
			}
		}

		if (selectedTextureID == mTextureCount - 1) {
			selectedTextureID = mTextureCount;
			mTextures[mTextureCount++] = texture;
		}

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, transform.Scale);
		model = glm::translate(model, transform.Position);
		// TODO: Add rotation later
		//model = glm::rotate(model, transform.Rotation.y, glm::vec3());

		Vertex* vertices = (Vertex*)vertexBuffer->GetData();
		uint32_t* indices = (uint32_t*)indexBuffer->GetData();

		for (uint8_t i = 0; i < 4; i++) {
			mVertices[mBatchCount * 4 + i].Position = glm::vec3(model * glm::vec4(vertices[i].Position, 1.0f));
			mVertices[mBatchCount * 4 + i].TexCoords = vertices[i].TexCoords;
			mVertices[mBatchCount * 4 + i].TextureID = selectedTextureID;
			mVertices[mBatchCount * 4 + i].FlipVertical = sprite->GetFlipVertical();
			mVertices[mBatchCount * 4 + i].FlipHorizontal = sprite->GetFlipHorizontal();
			mVertices[mBatchCount * 4 + i].Color = sprite->GetColor();
		}

		for (uint8_t i = 0; i < 6; i++) {
			mIndices[mBatchCount * 6 + i] = indices[i] + mBatchCount * 4;
		}

		mBatchCount++;
    }
}
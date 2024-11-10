#include"RenderBatch.h"
#include"Renderer/Renderer.h"
#include"Renderer/RenderCommand.h"
#include"Resource/VertexArray.h"
#include"Resource/IndexBuffer.h"
#include"Resource/Texture2D.h"
#include"Resource/Shader.h"
#include"Resource/Sprite.h"

#include"Renderer/Camera/Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace VIEngine {
    RenderBatch::RenderBatch() : mBatchCount(0), mVertices(), mIndices(), mVertexFormat() {
		mVertexFormat.AddAttribute(EVertexAttributeType::Float3, "aPosition");
		mVertexFormat.AddAttribute(EVertexAttributeType::Float2, "aTexCoords");
		mVertexFormat.AddAttribute(EVertexAttributeType::Int, "aTextureID");
		mVertexFormat.AddAttribute(EVertexAttributeType::Int, "aFlipVertical");
		mVertexFormat.AddAttribute(EVertexAttributeType::Int, "aFlipHorizontal");
		mVertexFormat.AddAttribute(EVertexAttributeType::Float4, "aColor");

		mVertexArray = VertexArray::Create(mVertexFormat);
    }

    RenderBatch::~RenderBatch() {
		mVertexArray->Release();
	}

    void RenderBatch::SubmitVerticesAndIndices() {
		mVertexArray->Bind();
		mVertexArray->SetVertexBuffer(mVertices.data(), mVertexFormat.GetStride() * mBatchCount * 4);
		mVertexArray->SetIndexBuffer(mIndices.data(), sizeof(uint32_t) * mBatchCount * 6, mBatchCount * 6);
    }

    bool RenderBatch::HasSlot() const {
        return mBatchCount < MAX_BATCH_SIZE;
    }

	void RenderBatch::Insert(const SpriteBatch& spriteBatch)
	{
		glm::mat4 model = glm::mat4(1.0f);
		
		model = glm::translate(model, spriteBatch.SpriteTransform.Position);
		model = glm::rotate(model, glm::radians(spriteBatch.SpriteTransform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(spriteBatch.SpriteTransform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(spriteBatch.SpriteTransform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, spriteBatch.SpriteTransform.Scale);

		Vertex vertices[4] = {
			{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f)}, // top-left
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f)}, // bottom-left
			{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f)}, // bottom-right
			{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f)} // top-right
		};

		uint32_t indicies[6] = {
			0, 1, 2, // left-bottom triangle
			2, 3, 0 // right-top triangle
		};

		for (uint8_t i = 0; i < 4; i++) {
			mVertices[mBatchCount * 4 + i].Position = glm::vec3(model * glm::vec4(vertices[i].Position, 1.0f));
			mVertices[mBatchCount * 4 + i].TexCoords = vertices[i].TexCoords;
			mVertices[mBatchCount * 4 + i].TextureID = spriteBatch.SpriteContext->GetSampleTextureID();
			mVertices[mBatchCount * 4 + i].FlipVertical = spriteBatch.FlipVertical;
			mVertices[mBatchCount * 4 + i].FlipHorizontal = spriteBatch.FlipHorizontal;
			mVertices[mBatchCount * 4 + i].Color = spriteBatch.SpriteContext->GetColor();
		}

		for (uint8_t i = 0; i < 6; i++) {
			mIndices[mBatchCount * 6 + i] = indicies[i] + mBatchCount * 4;
		}

		mBatchCount++;
    }
}
#include"OpenGLVertexArray.h"
#include"Resource/VertexBuffer.h"
#include"Resource/IndexBuffer.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"

#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI(OpenGLVertexArray, VertexArray::RunTimeType)

	OpenGLVertexArray::OpenGLVertexArray(bool useBatchedVertex) : 
			mID(), mVertexBuffer(VertexBuffer::Create()), mIndexBuffer(IndexBuffer::Create())
	{
		Renderer::Submit([this, useBatchedVertex]() {
			glGenVertexArrays(1, &mID);
			glBindVertexArray(mID);
			// Vertex Buffer
			uint32_t vertexBufferID;
			glGenBuffers(1, &vertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			if (!useBatchedVertex) {
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
				glEnableVertexAttribArray(2);
			}
			else {
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BatchedVertex), (void*)offsetof(BatchedVertex, Position));
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BatchedVertex), (void*)offsetof(BatchedVertex, TexCoords));
				glEnableVertexAttribArray(1);
				glVertexAttribIPointer(2, 1, GL_INT, sizeof(BatchedVertex), (void*)offsetof(BatchedVertex, TextureID));
				glEnableVertexAttribArray(2);
				glVertexAttribIPointer(3, 1, GL_INT, sizeof(BatchedVertex), (void*)offsetof(BatchedVertex, FlipVertical));
				glEnableVertexAttribArray(3);
				glVertexAttribIPointer(4, 1, GL_INT, sizeof(BatchedVertex), (void*)offsetof(BatchedVertex, FlipHorizontal));
				glEnableVertexAttribArray(4);
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(BatchedVertex), (void*)offsetof(BatchedVertex, Color));
				glEnableVertexAttribArray(5);
			}
			mVertexBuffer->SetID(vertexBufferID);
			// Index Buffer
			uint32_t indexBufferID;
			glGenBuffers(1, &indexBufferID);
			mIndexBuffer->SetID(indexBufferID);
		});
	}

	OpenGLVertexArray::~OpenGLVertexArray() {

	}

	void OpenGLVertexArray::Release()
	{
		Renderer::Submit([this]() {
			glDeleteVertexArrays(1, &mID);
			ResourceManager::Get().FreeVertexArray(this);
		});
		mVertexBuffer->Release();
		mIndexBuffer->Release();
	}

	void OpenGLVertexArray::SetVertexBuffer(void* data, uint32_t size, ERendererMode mode)
	{
		// void* submitData = ResourceManager::Get().AllocateOnStack("VertexArray", size, alignof(uint32_t));
		void* submitData = malloc(size);
		memcpy(submitData, data, size);
		mVertexBuffer->SetData(submitData, size);
		mVertexBuffer->SetMode(mode);

		Renderer::Submit([this]() {
			glBindVertexArray(mID);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer->GetID());
			glBufferData(GL_ARRAY_BUFFER, mVertexBuffer->GetSize(), mVertexBuffer->GetData(), OpenGLFactory::ToOpenGLMode(mVertexBuffer->GetMode()));
		});
	}

	void OpenGLVertexArray::SetIndexBuffer(void* data, uint32_t size, uint32_t nums, ERendererMode mode)
	{
		// void* submitData = ResourceManager::Get().AllocateOnStack("IndexBuffer", size, alignof(uint32_t));
		void* submitData = malloc(size);
		memcpy(submitData, data, size);
		mIndexBuffer->SetData(submitData, size);
		mIndexBuffer->SetNums(nums);
		mIndexBuffer->SetMode(mode);
		
		Renderer::Submit([this]() {
			glBindVertexArray(mID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer->GetID());
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer->GetSize(), mIndexBuffer->GetData(), OpenGLFactory::ToOpenGLMode(mIndexBuffer->GetMode()));
		});
	}

	void OpenGLVertexArray::Bind()
	{
		Renderer::Submit([this]() {
			glBindVertexArray(mID);
		});
	}

	void OpenGLVertexArray::Unbind()
	{
		Renderer::Submit([]() {
			glBindVertexArray(0);
		});
	}
}
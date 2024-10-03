#include"OpenGLVertexArray.h"
#include"Resource/VertexBuffer.h"
#include"Resource/IndexBuffer.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"

#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI(OpenGLVertexArray, VertexArray::RunTimeType)

	OpenGLVertexArray::OpenGLVertexArray() : 
			mID(), mVertexBuffer(VertexBuffer::Create()), mIndexBuffer(IndexBuffer::Create())
	{
		Renderer::Submit([this]() {
			glGenVertexArrays(1, &mID);
			glBindVertexArray(mID);
			// Vertex Buffer
			uint32_t vertexBufferID;
			glGenBuffers(1, &vertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
			glEnableVertexAttribArray(2);
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
		mVertexBuffer->SetSize(size);
		void* submitData = ResourceManager::Get().AllocatePerFrame(size, alignof(uint32_t));
		memcpy(submitData, data, mVertexBuffer->GetSize());

		Renderer::Submit([submitData, mode, this]() {
			glBindVertexArray(mID);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer->GetID());
			glBufferData(GL_ARRAY_BUFFER, mVertexBuffer->GetSize(), submitData, OpenGLFactory::ToOpenGLMode(mode));
		});
	}

	void OpenGLVertexArray::SetIndexBuffer(void* data, uint32_t size, uint32_t nums, ERendererMode mode)
	{
		mIndexBuffer->SetSize(size);
		mIndexBuffer->SetNums(nums);

		void* submitData = ResourceManager::Get().AllocatePerFrame(size, alignof(uint32_t));
		memcpy(submitData, data, size);
		Renderer::Submit([submitData, mode, this]() {
			glBindVertexArray(mID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer->GetID());
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer->GetSize(), submitData, OpenGLFactory::ToOpenGLMode(mode));
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
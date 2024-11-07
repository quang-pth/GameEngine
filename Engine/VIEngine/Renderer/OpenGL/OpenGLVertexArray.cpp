#include"OpenGLVertexArray.h"
#include"Resource/VertexBuffer.h"
#include"Resource/IndexBuffer.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"
#include"Core/Application.h"

#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI(OpenGLVertexArray, VertexArray::RunTimeType)
	
	OpenGLVertexArray::OpenGLVertexArray(const VertexFormat& vertexFormat) 
		: mID(), mVertexFormat(vertexFormat), mVertexBuffer(VertexBuffer::Create()), mIndexBuffer(IndexBuffer::Create())
	{
		Renderer::Submit([this]() {
			glGenVertexArrays(1, &mID);
			glBindVertexArray(mID);
			// Vertex Buffer
			uint32_t vertexBufferID;
			glGenBuffers(1, &vertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			for (const VertexAttribute& attribute : mVertexFormat.GetVertexAttributes()) {
				if (
					attribute.Type == EVertexAttributeType::Int ||
					attribute.Type == EVertexAttributeType::Int2 ||
					attribute.Type == EVertexAttributeType::Int3 ||
					attribute.Type == EVertexAttributeType::Int4
				)
				{
					glVertexAttribIPointer(attribute.Location, attribute.NumsComponent, GL_INT, mVertexFormat.GetStride(), (void*)attribute.Offset);
					glEnableVertexAttribArray(attribute.Location);
				}
				else {
					glVertexAttribPointer(attribute.Location, attribute.NumsComponent, GL_FLOAT, attribute.Normalized ? GL_TRUE : GL_FALSE, mVertexFormat.GetStride(), (void*)attribute.Offset);
					glEnableVertexAttribArray(attribute.Location);
				}
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
		void* submitData = ResourceManager::Get().AllocatePerFrame(size, alignof(uint32_t));
		//void* submitData = malloc(size);
		memcpy(submitData, data, size);
		mVertexBuffer->SetData(submitData, size);
		mVertexBuffer->SetMode(mode);

		Renderer::Submit([this]() {
			glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer->GetID());
			glBufferData(GL_ARRAY_BUFFER, mVertexBuffer->GetSize(), mVertexBuffer->GetData(), OpenGLFactory::ToOpenGLMode(mVertexBuffer->GetMode()));
		});
	}

	void OpenGLVertexArray::SetIndexBuffer(void* data, uint32_t size, uint32_t nums, ERendererMode mode)
	{
		void* submitData = ResourceManager::Get().AllocatePerFrame(size, alignof(uint32_t));
		//void* submitData = malloc(size);
		memcpy(submitData, data, size);
		mIndexBuffer->SetData(submitData, size);
		mIndexBuffer->SetNums(nums);
		mIndexBuffer->SetMode(mode);
		
		Renderer::Submit([this]() {
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
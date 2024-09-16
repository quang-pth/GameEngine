#include"OpenGLVertexBuffer.h"

#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"
#include<glad/gl.h>
	
namespace VIEngine {
	DEFINE_RTTI(OpenGLVertexBuffer, VertexBuffer::RunTimeType)

	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		Renderer::Submit([this]() {
			glGenBuffers(1, &mID);
			glBindBuffer(GL_ARRAY_BUFFER, mID);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
			glEnableVertexAttribArray(2);
		});
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{

	}

	void OpenGLVertexBuffer::Release() {
		Renderer::Submit([this]() {
			glDeleteBuffers(1, &mID);
			ResourceManager::Get().FreeVertexBuffer(this);
		});
	}

	void OpenGLVertexBuffer::Bind()
	{
		Renderer::Submit([this]() {
			glBindBuffer(GL_ARRAY_BUFFER, mID);
		});
	}

	void OpenGLVertexBuffer::Unbind()
	{
		Renderer::Submit([this]() {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		});
	}

	void OpenGLVertexBuffer::SetData(void* data, uint32_t size, ERendererMode mode)
	{
		void* submitData = ResourceManager::Get().AllocatePerFrame(size, alignof(uint32_t));
		memcpy(submitData, data, size);
		Renderer::Submit([submitData, size, mode, this]() {
			glBindBuffer(GL_ARRAY_BUFFER, mID);
			glBufferData(GL_ARRAY_BUFFER, size, submitData, OpenGLFactory::ToOpenGLMode(mode));
		});
	}
}
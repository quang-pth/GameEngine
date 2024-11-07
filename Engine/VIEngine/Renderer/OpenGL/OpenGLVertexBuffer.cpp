#include"OpenGLVertexBuffer.h"

#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"
#include"Core/Logger/Logger.h"
#include"Core/Application.h"
#include<glad/gl.h>
	
namespace VIEngine {
	DEFINE_RTTI(OpenGLVertexBuffer, VertexBuffer::RunTimeType)

	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{

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
}
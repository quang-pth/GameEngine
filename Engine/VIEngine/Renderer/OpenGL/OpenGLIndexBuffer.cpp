#include"OpenGLIndexBuffer.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"

#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI(OpenGLIndexBuffer, IndexBuffer::RunTimeType)

	OpenGLIndexBuffer::OpenGLIndexBuffer() {

	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
	}

	void OpenGLIndexBuffer::Release()
	{
		Renderer::Submit([this]() {
			glDeleteBuffers(1, &mID);
			ResourceManager::Get().FreeIndexBuffer(this);
		});
	}

	void OpenGLIndexBuffer::Bind()
	{
		Renderer::Submit([this]() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
		});
	}

	void OpenGLIndexBuffer::Unbind()
	{
		Renderer::Submit([]() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		});
	}
}
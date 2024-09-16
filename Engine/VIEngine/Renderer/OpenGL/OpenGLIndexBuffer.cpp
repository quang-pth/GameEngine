#include"OpenGLIndexBuffer.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"

#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI(OpenGLIndexBuffer, IndexBuffer::RunTimeType)

	OpenGLIndexBuffer::OpenGLIndexBuffer() {
		Renderer::Submit([this]() {
			glGenBuffers(1, &mID);
		});
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

	void OpenGLIndexBuffer::SetData(void* data, uint32_t size, uint32_t nums, ERendererMode mode)
	{
		mSize = size;
		mNums = nums;
		void* submitData = ResourceManager::Get().AllocatePerFrame(size, alignof(uint32_t));
		memcpy(submitData, data, size);

		Renderer::Submit([submitData, mode, this]() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize, submitData, OpenGLFactory::ToOpenGLMode(mode));
		});
	}
}
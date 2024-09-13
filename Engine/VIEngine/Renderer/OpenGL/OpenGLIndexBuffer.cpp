#include"OpenGLIndexBuffer.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"

#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI(OpenGLIndexBuffer, IndexBuffer::RunTimeType)

	OpenGLIndexBuffer::OpenGLIndexBuffer() : mID() {
		Renderer::Submit([this]() {
			glGenBuffers(1, &mID);
		});
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		Renderer::Submit([this]() {
			glDeleteBuffers(1, &mID);
			ResourceManager::Get().FreeIndexBuffer(this);
		});
	}

	void OpenGLIndexBuffer::Bind() {
		Renderer::Submit([this]() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
		});
	}

	void OpenGLIndexBuffer::Unbind() {
		Renderer::Submit([]() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		});
	}

	void OpenGLIndexBuffer::SetData(uint32_t* data, uint32_t size) {
		mSize = size;
		mNums = size / sizeof(uint32_t);
		void* submitData = ResourceManager::Get().AllocatePerFrame(size, alignof(uint32_t));
		memcpy(submitData, data, size);
		Renderer::Submit([submitData, this]() {
			//uint32_t index = *((uint32_t*)submitData + 2);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize, submitData, GL_STATIC_DRAW);
		});
	}
}
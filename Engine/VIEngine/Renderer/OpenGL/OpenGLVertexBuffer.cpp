#include"OpenGLVertexBuffer.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"OpenGLFactory.h"

#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI(OpenGLVertexBuffer, VertexBuffer::RunTimeType)

	OpenGLVertexBuffer::OpenGLVertexBuffer() : mID(), mSize() {
		Renderer::Submit([this]() {
			glGenBuffers(1, &mID);
			glBindBuffer(GL_ARRAY_BUFFER, mID);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position)); // Position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoords)); // Texture coordinates
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color)); // Color
			glEnableVertexAttribArray(2);
		});
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		Renderer::Submit([this]() {
			glDeleteBuffers(1, &mID);
			ResourceManager::Get().FreeVertexBuffer(this);
		});
	}

	void OpenGLVertexBuffer::Bind() {
		Renderer::Submit([this]() {
			glBindBuffer(GL_VERTEX_ARRAY, mID);
		});
	}

	void OpenGLVertexBuffer::Unbind() {
		Renderer::Submit([]() {
			glBindBuffer(GL_VERTEX_ARRAY, 0);
		});
	}

	void OpenGLVertexBuffer::SetData(void* data, uint32_t size, ERendererMode mode) {
		void* submitData = ResourceManager::Get().AllocatePerFrame(size, alignof(uint32_t));
		memcpy(submitData, data, size);
		Renderer::Submit([submitData, size, mode, this]() {
			//Vertex vertex = *(Vertex*)submitData;
			glBindBuffer(GL_ARRAY_BUFFER, mID);
			glBufferData(GL_ARRAY_BUFFER, size, submitData, OpenGLFactory::ToOpenGLMode(mode));
		});
	}
}
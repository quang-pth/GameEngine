#include"OpenGLVertexBuffer.h"

namespace VIEngine {
	DEFINE_RTTI(OpenGLVertexBuffer, &VertexBuffer::RunTimeType)

	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		glGenBuffers(1, &mID);
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		//CORE_LOG_TRACE("{0}", vertexBuffer->GetData()[0].Position.Y);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position)); // Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoords)); // Texture coordinates
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color)); // Color
		glEnableVertexAttribArray(2);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &mID);
	}

	void OpenGLVertexBuffer::SetData(const void* vertices, uint32_t nums) {
		mSize = sizeof(Vertex) * nums;
		mStride = sizeof(Vertex);
		mVertices = vertices;
	}
}
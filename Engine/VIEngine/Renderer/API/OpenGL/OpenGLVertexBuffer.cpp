#include"OpenGLVertexBuffer.h"

namespace VIEngine {
	DEFINE_RTTI(OpenGLVertexBuffer, &VertexBuffer::RunTimeType)

	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		glGenBuffers(1, &mID);
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
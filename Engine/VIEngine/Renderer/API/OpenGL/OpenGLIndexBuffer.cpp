#include"OpenGLIndexBuffer.h"
#include<glad/gl.h>
#include"Core/Logger/Logger.h"

namespace VIEngine {
	DEFINE_RTTI(OpenGLIndexBuffer, &IndexBuffer::RunTimeType)
}

namespace VIEngine {
	OpenGLIndexBuffer::OpenGLIndexBuffer() {
		glGenBuffers(1, &mID);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &mID);
	}

	void OpenGLIndexBuffer::SetData(const void* indices, uint32_t nums) {
		mIndices = indices;
		mNums = nums;
	}
}
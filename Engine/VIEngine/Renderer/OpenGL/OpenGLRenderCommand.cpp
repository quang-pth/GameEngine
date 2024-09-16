#include"Renderer/RenderCommand.h"
#include"OpenGLFactory.h"

#define GLAD_GL_IMPLEMENTATION
#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(OpenGLRenderCommand)

	OpenGLRenderCommand::OpenGLRenderCommand() {
		glGenVertexArrays(1, &mVertexArrayID);
		glBindVertexArray(mVertexArrayID);
	}

	OpenGLRenderCommand::~OpenGLRenderCommand() {
		glDeleteVertexArrays(1, &mVertexArrayID);
	}

	void OpenGLRenderCommand::ClearColorImpl(float r, float g, float b, float w) {
		glClearColor(r, g, b, w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderCommand::DrawIndexedImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) {
		glDrawElements(OpenGLFactory::ToOpenGLPrimitive(primitive), nums, GL_UNSIGNED_INT, (void*)offset);
	}
}
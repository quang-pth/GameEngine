#include"Renderer/RenderCommand.h"1

#define GLAD_GL_IMPLEMENTATION
#include<glad/gl.h>
#include"OpenGLFactory.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(OpenGLRenderCommand)

	OpenGLRenderCommand::OpenGLRenderCommand() {
		glGenVertexArrays(1, &mVertexArrayID);
		glBindVertexArray(mVertexArrayID);
	}

	void OpenGLRenderCommand::ClearColorImpl(float r, float g, float b, float w) {
		glClearColor(r, g, b, w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderCommand::DrawIndexedImpl(uint32_t count, ERendererPrimitive renderMode, uint32_t offset) {
		glDrawElements(OpenGLFactory::ToOpenGLPrimitive(renderMode), count, GL_UNSIGNED_INT, (void*)offset);
	}
}
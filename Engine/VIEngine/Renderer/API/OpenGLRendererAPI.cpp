#include"OpenGLRendererAPI.h"

#include<glad/gl.h>

namespace VIEngine {
	OpenGLRendererAPI::OpenGLRendererAPI() {
		RendererAPI::sRendererAPI = this;
	}

	void OpenGLRendererAPI::ClearColorImpl(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererAPI::BindVertexBufferImpl(const VertexBuffer* vertexBuffer)
	{
	}

	void OpenGLRendererAPI::UnbindVertexBufferImpl(const VertexBuffer* vertexBuffer)
	{
	}

	void OpenGLRendererAPI::BindIndexBufferImpl(const IndexBuffer* indexBuffer)
	{
	}

	void OpenGLRendererAPI::UnbindIndexBufferImpl(const IndexBuffer* indexBuffer)
	{
	}

	void OpenGLRendererAPI::BindShaderImpl(const Shader* shader)
	{
	}

	void OpenGLRendererAPI::UnbindShaderImpl(const Shader*)
	{
	}
}
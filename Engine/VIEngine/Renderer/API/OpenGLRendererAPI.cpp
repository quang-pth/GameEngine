#include"OpenGLRendererAPI.h"
#include"OpenGL/OpenGLVertexBuffer.h"
#include"OpenGL/OpenGLShader.h"
#include"OpenGL/OpenGLIndexBuffer.h"
#include"Core/Cast/Cast.h"
#include"Core/Logger/Logger.h"
#include<glad/gl.h>

namespace VIEngine {
	static GLenum ToOpenGLUsage(ERendererAPIUsage usage) {
		if (usage == ERendererAPIUsage::STATIC_DRAW) return GL_STATIC_DRAW;
		if (usage == ERendererAPIUsage::DYNAMIC_DRAW) return GL_DYNAMIC_DRAW;
		if (usage == ERendererAPIUsage::STREAM_DRAW) return GL_STREAM_DRAW;

		return GL_STATIC_DRAW;
	}
	
	static GLenum ToOpenGLPrimitive(EPrimitive primitive) {
		if (primitive == EPrimitive::TRIANGLE) return GL_TRIANGLES;
		if (primitive == EPrimitive::POINT) return GL_POINTS;
		if (primitive == EPrimitive::LINE) return GL_LINE;

		return GL_TRIANGLES;
	}

	OpenGLRendererAPI::OpenGLRendererAPI() {
		RendererAPI::sRendererAPI = this;
	}

	VertexBuffer* OpenGLRendererAPI::CreateVertexBufferImpl()
	{
		return ResourceManager::Get().NewOnStack<OpenGLVertexBuffer>(OpenGLVertexBuffer::RunTimeType.GetTypeName());
	}

	IndexBuffer* OpenGLRendererAPI::CreateIndexBufferImpl()
	{
		return ResourceManager::Get().NewOnStack<OpenGLIndexBuffer>(OpenGLIndexBuffer::RunTimeType.GetTypeName());
	}

	Shader* OpenGLRendererAPI::CreateShaderImpl(const char* filepath /*assume the filepath is in glsl format*/)
	{
		OpenGLShader* shader = DownCast<OpenGLShader>(ResourceManager::Get().GetShader(filepath));
		if (shader != nullptr) {
			CORE_LOG_TRACE("Shader {0} is already loaded, so reuse it", filepath);
			return shader;
		}

		auto sources = ResourceManager::Get().ParseSourceGLSL(filepath);
		shader = ResourceManager::Get().NewOnStack<OpenGLShader>(OpenGLShader::RunTimeType.GetTypeName(), sources["vertex"].c_str(), sources["fragment"].c_str());
		ResourceManager::Get().SaveShader(filepath, shader);
		
		return shader;
	}

	void OpenGLRendererAPI::OnInit() {
		glGenVertexArrays(1, &mVertexArrayID);
		glBindVertexArray(mVertexArrayID);
	}

	void OpenGLRendererAPI::OnShutdown() {
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &mVertexArrayID);
	}

	void OpenGLRendererAPI::ClearColorImpl(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererAPI::BindVertexBufferImpl(const VertexBuffer* vertexBuffer, ERendererAPIUsage usage)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GetID());
		glBufferData(GL_ARRAY_BUFFER, vertexBuffer->GetSize(), vertexBuffer->GetData(), ToOpenGLUsage(usage));
		//CORE_LOG_TRACE("{0}", vertexBuffer->GetData()[0].Position.Y);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexBuffer->GetStride(), (void*)offsetof(Vertex, Position)); // Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexBuffer->GetStride(), (void*)offsetof(Vertex, TextureCoords)); // Texture coordinates
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertexBuffer->GetStride(), (void*)offsetof(Vertex, Color)); // Color
		glEnableVertexAttribArray(2);
	}

	void OpenGLRendererAPI::UnBindVertexBufferImpl(const VertexBuffer* vertexBuffer)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLRendererAPI::BindIndexBufferImpl(const IndexBuffer* indexBuffer, ERendererAPIUsage usage)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->GetID());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->GetSize(), indexBuffer->GetData(), ToOpenGLUsage(usage));
	}

	void OpenGLRendererAPI::UnBindIndexBufferImpl(const IndexBuffer* indexBuffer)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLRendererAPI::BindShaderImpl(const Shader* shader)
	{
		glUseProgram(shader->GetID());
	}

	void OpenGLRendererAPI::UnBindShaderImpl(const Shader*)
	{
	}

	void OpenGLRendererAPI::DrawIndexedImpl(uint32_t nums, EPrimitive primitive) {
		glDrawElements(ToOpenGLPrimitive(primitive), nums, GL_UNSIGNED_INT, 0);
	}
}
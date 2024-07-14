#include"RendererAPI.h"

namespace VIEngine {
	RendererAPI* RendererAPI::sRendererAPI = nullptr;

	VertexBuffer* RendererAPI::CreateVertexBuffer() {
		return sRendererAPI->CreateVertexBufferImpl();
	}
	
	IndexBuffer* RendererAPI::CreateIndexBuffer() {
		return sRendererAPI->CreateIndexBufferImpl();
	}
	
	Shader* RendererAPI::CreateShader(const char* filepath) {
		return sRendererAPI->CreateShaderImpl(filepath);
	}

	void RendererAPI::ClearColor(float r, float g, float b, float a) {
		sRendererAPI->ClearColorImpl(r, g, b, a);
	}

	void RendererAPI::BindVertexBuffer(const VertexBuffer* vertexBuffer, ERendererAPIUsage usage)
	{
		sRendererAPI->BindVertexBufferImpl(vertexBuffer, usage);
	}

	void RendererAPI::BindIndexBuffer(const IndexBuffer* indexBuffer, ERendererAPIUsage usage)
	{
		sRendererAPI->BindIndexBufferImpl(indexBuffer, usage);
	}

	void RendererAPI::BindShader(const Shader* shader)
	{
		sRendererAPI->BindShaderImpl(shader);
	}

	void RendererAPI::UnBindVertexBuffer(const VertexBuffer* vertexBuffer)
	{
		sRendererAPI->UnBindVertexBufferImpl(vertexBuffer);
	}

	void RendererAPI::UnBindIndexBuffer(const IndexBuffer* indexBuffer)
	{
		sRendererAPI->UnBindIndexBufferImpl(indexBuffer);
	}

	void RendererAPI::UnBindShader(const Shader* shader)
	{
		sRendererAPI->UnBindShaderImpl(shader);
	}

	void RendererAPI::DrawIndexed(uint32_t nums, EPrimitive primitive) {
		sRendererAPI->DrawIndexedImpl(nums, primitive);
	}

} // namespace VIEngine

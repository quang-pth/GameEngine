#include"RendererAPI.h"

namespace VIEngine {
	RendererAPI* RendererAPI::sRendererAPI = nullptr;

	VertexBuffer* RendererAPI::CreateVertexBuffer() {
		return sRendererAPI->CreateVertexBuffer();
	}
	
	IndexBuffer* RendererAPI::CreateIndexBuffer() {
		return sRendererAPI->CreateIndexBuffer();
	}
	
	Shader* RendererAPI::CreateShader() {
		return sRendererAPI->CreateShader();
	}

	void RendererAPI::ClearColor(float r, float g, float b, float a) {
		sRendererAPI->ClearColorImpl(r, g, b, a);
	}
} // namespace VIEngine

#pragma once

#include"Renderer/API/RendererAPI.h"

namespace VIEngine {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI();
	protected:
		virtual VertexBuffer* CreateVertexBufferImpl() override;
		virtual IndexBuffer* CreateIndexBufferImpl() override;
		virtual Shader* CreateShaderImpl(const char* filepath) override;
		virtual void OnInit() override;
		virtual void OnShutdown() override;
		virtual void ClearColorImpl(float r, float g, float b, float a = 1.0f) override;
		virtual void BindVertexBufferImpl(const VertexBuffer*, ERendererAPIUsage usage) override;
		virtual void BindIndexBufferImpl(const IndexBuffer*, ERendererAPIUsage usage) override;
		virtual void BindShaderImpl(const Shader*) override;
		virtual void UnBindVertexBufferImpl(const VertexBuffer*) override;
		virtual void UnBindIndexBufferImpl(const IndexBuffer*) override;
		virtual void UnBindShaderImpl(const Shader*) override;
		virtual void DrawIndexedImpl(uint32_t nums, EPrimitive primitive) override;
	private:
		uint32_t mVertexArrayID;
	};
}
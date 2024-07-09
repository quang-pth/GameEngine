#pragma once

#include"Renderer/API/RendererAPI.h"

namespace VIEngine {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI();

		virtual void ClearColorImpl(float r, float g, float b, float a = 1.0f) override;
		virtual void BindVertexBufferImpl(const VertexBuffer*) override;
		virtual void UnbindVertexBufferImpl(const VertexBuffer*) override;
		virtual void BindIndexBufferImpl(const IndexBuffer*) override;
		virtual void UnbindIndexBufferImpl(const IndexBuffer*) override;
		virtual void BindShaderImpl(const Shader*) override;
		virtual void UnbindShaderImpl(const Shader*) override;
	};
}
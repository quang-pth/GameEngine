#pragma once

#include"Resource/Resource.h"

namespace VIEngine {
	enum class ERendererAPI {
		OpenGL,
		DirectX
	};

	class RendererAPI {
	public:
		static VertexBuffer* CreateVertexBuffer();
		static IndexBuffer* CreateIndexBuffer();
		static Shader* CreateShader();
		static void ClearColor(float r, float g, float b, float a = 1.0f);

	public:
		virtual ~RendererAPI() = default;

		virtual void ClearColorImpl(float r, float g, float b, float a = 1.0f) = 0;
		virtual void BindVertexBufferImpl(const VertexBuffer*) = 0;
		virtual void UnbindVertexBufferImpl(const VertexBuffer*) = 0;
		virtual void BindIndexBufferImpl(const IndexBuffer*) = 0;
		virtual void UnbindIndexBufferImpl(const IndexBuffer*) = 0;
		virtual void BindShaderImpl(const Shader*) = 0;
		virtual void UnbindShaderImpl(const Shader*) = 0;
	protected:
		RendererAPI() = default;
	protected:
		static RendererAPI* sRendererAPI;
	};
}
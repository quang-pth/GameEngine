#pragma once

#include"Resource/Resource.h"
#include"pch.h"

namespace VIEngine {
	enum class ERendererAPI {
		OpenGL,
		DirectX
	};

	enum class ERendererAPIUsage {
		STATIC_DRAW,
		DYNAMIC_DRAW,
		STREAM_DRAW
	};

	enum class EShaderType {
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		PROGRAM
	};

	enum class EPrimitive {
		TRIANGLE,
		LINE,
		POINT
	};

	class VI_API RendererAPI {
	public:
		static VertexBuffer* CreateVertexBuffer();
		static IndexBuffer* CreateIndexBuffer();
		static Shader* CreateShader(const char* filepath);

	public:
		static void ClearColor(float r, float g, float b, float a = 1.0f);
		static void BindVertexBuffer(const VertexBuffer*, ERendererAPIUsage usage = ERendererAPIUsage::STATIC_DRAW);
		static void BindIndexBuffer(const IndexBuffer*, ERendererAPIUsage usage = ERendererAPIUsage::STATIC_DRAW);
		static void BindShader(const Shader*);

		static void UnBindVertexBuffer(const VertexBuffer*);
		static void UnBindIndexBuffer(const IndexBuffer*);
		static void UnBindShader(const Shader*);

		static void DrawIndexed(uint32_t nums, EPrimitive primitive = EPrimitive::TRIANGLE);

	public:
		virtual ~RendererAPI() = default;
		virtual void OnInit() = 0;
		virtual void OnShutdown() = 0;
	protected:
		virtual VertexBuffer* CreateVertexBufferImpl() = 0;
		virtual IndexBuffer* CreateIndexBufferImpl() = 0;
		virtual Shader* CreateShaderImpl(const char* filepath) = 0;
		virtual void ClearColorImpl(float r, float g, float b, float a = 1.0f) = 0;
		virtual void BindVertexBufferImpl(const VertexBuffer*, ERendererAPIUsage usage) = 0;
		virtual void BindIndexBufferImpl(const IndexBuffer*, ERendererAPIUsage usage) = 0;
		virtual void BindShaderImpl(const Shader*) = 0;
		virtual void UnBindVertexBufferImpl(const VertexBuffer*) = 0;
		virtual void UnBindIndexBufferImpl(const IndexBuffer*) = 0;
		virtual void UnBindShaderImpl(const Shader*) = 0;
		
		virtual void DrawIndexedImpl(uint32_t nums, EPrimitive primitive) = 0;
	protected:
		RendererAPI() = default;
	protected:
		static RendererAPI* sRendererAPI;
	};
}
#pragma once

#include"pch.h"
#include"Core/Type/Object.h"
#include"Renderer/RendererAPI.h"
#include"VertexFormat.h"

namespace VIEngine {
	class VI_API VertexArray : public Object {
	public:
		DECLARE_RTTI
	public:
		static VertexArray* Create(bool useBatchedVertex = false);
		static VertexArray* Create(const VertexFormat& vertexFormat);
	public:
		virtual ~VertexArray() = default;
		virtual class VertexBuffer* GetVertexBuffer() = 0;
		virtual class IndexBuffer* GetIndexBuffer() = 0;
		virtual void Release() = 0;
		virtual void SetVertexBuffer(void* data, uint32_t size, ERendererMode mode = ERendererMode::Static) = 0;
		virtual void SetIndexBuffer(void* data, uint32_t size, uint32_t nums, ERendererMode mode = ERendererMode::Static) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	protected:
		VertexArray() = default;
	};
}
#pragma once

#include"Resource/VertexArray.h"

namespace VIEngine {
	class VI_API OpenGLVertexArray : public VertexArray {
	public:
		DECLARE_RTTI
	public:
		OpenGLVertexArray(bool useBatchedVertex = false);
		~OpenGLVertexArray();
		VI_FORCE_INLINE virtual class VertexBuffer* GetVertexBuffer() override { return mVertexBuffer; }
		VI_FORCE_INLINE virtual class IndexBuffer* GetIndexBuffer() override { return mIndexBuffer; }
		virtual void Release() override;
		virtual void SetVertexBuffer(void* data, uint32_t size, ERendererMode mode = ERendererMode::Static) override;
		virtual void SetIndexBuffer(void* data, uint32_t size, uint32_t nums, ERendererMode mode = ERendererMode::Static) override;
		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t mID;
		class VertexBuffer* mVertexBuffer;
		class IndexBuffer* mIndexBuffer;
	};
}
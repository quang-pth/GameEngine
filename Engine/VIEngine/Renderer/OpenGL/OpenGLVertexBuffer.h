#pragma once

#include"Resource/VertexBuffer.h"

namespace VIEngine {
	class VI_API OpenGLVertexBuffer : public VertexBuffer {
	public:
		DECLARE_RTTI

	public:
		OpenGLVertexBuffer();
		~OpenGLVertexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;
		VI_FORCE_INLINE virtual uint32_t GetID() override { return mID; }
		VI_FORCE_INLINE virtual uint32_t GetSize() override { return mSize; }
		virtual void SetData(void* data, uint32_t size, ERendererMode mode = ERendererMode::Static);

	private:
		uint32_t mID, mSize;
	};
}
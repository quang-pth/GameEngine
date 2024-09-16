#pragma once

#include"Resource/VertexBuffer.h"

namespace VIEngine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		DECLARE_RTTI
	public:
		OpenGLVertexBuffer();
		~OpenGLVertexBuffer();

		virtual void Release() override;
		virtual void Bind() override;
		virtual void Unbind() override;
 		VI_FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		VI_FORCE_INLINE virtual uint32_t GetSize() const override { return mSize; }
		virtual void SetData(void* data, uint32_t size, ERendererMode mode = ERendererMode::Static) override;
	private:
		uint32_t mID, mSize;
	};
}
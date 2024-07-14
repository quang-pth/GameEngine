#pragma once

#include"Resource/Resource.h"

namespace VIEngine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		DECLARE_RTTI
	public:
		OpenGLVertexBuffer();
		~OpenGLVertexBuffer();

		VI_FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		VI_FORCE_INLINE virtual uint32_t GetSize() const override { return mSize; }
		VI_FORCE_INLINE virtual uint32_t GetStride() const override { return mStride; }
		VI_FORCE_INLINE virtual const void* GetData() const override { return mVertices; }
		VI_FORCE_INLINE virtual void SetData(const void*, uint32_t) override;

	private:
		uint32_t mID, mSize, mStride;
		const void* mVertices;
	};
}
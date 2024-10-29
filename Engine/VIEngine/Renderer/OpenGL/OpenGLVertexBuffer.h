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
		VI_FORCE_INLINE virtual void* GetData() const override { return mData; }
		VI_FORCE_INLINE virtual ERendererMode GetMode() const override { return mMode; }
		VI_FORCE_INLINE virtual void SetID(uint32_t id) override { mID = id; }
		VI_FORCE_INLINE virtual void SetData(void* data, uint32_t size) override { mData = data; mSize = size; }
		VI_FORCE_INLINE virtual void SetMode(ERendererMode mode) override { mMode = mode; }
	private:
		uint32_t mID, mSize;
		void* mData;
		ERendererMode mMode;
	};
}
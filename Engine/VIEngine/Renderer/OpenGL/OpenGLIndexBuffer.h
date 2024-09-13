#pragma once

#include"Resource/IndexBuffer.h"

namespace VIEngine {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		DECLARE_RTTI
	public:
		OpenGLIndexBuffer();
		~OpenGLIndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;
		VI_FORCE_INLINE virtual uint32_t GetID() override { return mID; }
		VI_FORCE_INLINE virtual uint32_t GetSize() override { return mSize; }
		VI_FORCE_INLINE virtual uint32_t GetNums() override { return mNums; }
		virtual void SetData(uint32_t* data, uint32_t size) override;
	private:
		uint32_t mID, mSize, mNums, mOffset;
	};
}
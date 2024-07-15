#pragma once

#include"Resource/Resource.h"

namespace VIEngine {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		DECLARE_RTTI
	public:
		OpenGLIndexBuffer();
		~OpenGLIndexBuffer();
		VI_FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		VI_FORCE_INLINE virtual uint32_t GetSize() const override { return sizeof(uint32_t) * mNums; }
		VI_FORCE_INLINE virtual uint32_t GetNums() const override { return mNums; }
		VI_FORCE_INLINE virtual const void* GetData() const override { return mIndices; }
		virtual void SetData(const void* indices, uint32_t nums) override;
	private:
		uint32_t mID, mNums;
		const void* mIndices;
	};
}
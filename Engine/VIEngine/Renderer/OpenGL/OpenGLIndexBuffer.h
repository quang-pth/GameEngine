#pragma once

#include"Resource/IndexBuffer.h"

namespace VIEngine {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		DECLARE_RTTI
	public:
		OpenGLIndexBuffer();
		~OpenGLIndexBuffer();
		virtual void Release() override;
		virtual void Bind() override;
		virtual void Unbind() override;
		VI_FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		VI_FORCE_INLINE virtual uint32_t GetSize() const override { return mSize; }
		VI_FORCE_INLINE virtual uint32_t GetNums() const override { return mNums; }
		VI_FORCE_INLINE virtual void* GetData() const override { return mData; }
		VI_FORCE_INLINE virtual ERendererMode GetMode() const override { return mMode; }
		virtual void SetID(uint32_t id) override { mID = id; }
		virtual void SetNums(uint32_t nums) override { mNums = nums; }
		virtual void SetData(void* data, uint32_t size) override { mData = data; mSize = size; }
		virtual void SetMode(ERendererMode mode) override { mMode = mode; }
	private:
		uint32_t mID, mSize, mNums;
		void* mData;
		ERendererMode mMode;
	};
}
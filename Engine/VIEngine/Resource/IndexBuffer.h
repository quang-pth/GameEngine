#pragma once

#include"pch.h"
#include"Core/Type/Object.h"

namespace VIEngine {
	class VI_API IndexBuffer : public Object {
	public:
		DECLARE_RTTI
	public:
		virtual ~IndexBuffer() = default;
		virtual uint32_t GetID() const = 0;
		virtual uint32_t GetSize() const = 0;
		virtual uint32_t GetNums() const = 0;
		virtual const void* GetData() const = 0;
		virtual void SetData(const void* indices, uint32_t nums) = 0;
	protected:
		IndexBuffer() = default;
	};
}
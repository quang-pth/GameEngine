#pragma once

#include"pch.h"
#include"Core/Type/Object.h"

namespace VIEngine {
	class VI_API IndexBuffer : public Object {
	public:
		DECLARE_RTTI
	public:
		static IndexBuffer* Create();
	
	public:
		virtual ~IndexBuffer() = default;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetID() = 0;
		virtual uint32_t GetSize() = 0;
		virtual uint32_t GetNums() = 0;
		virtual void SetData(uint32_t* data, uint32_t size) = 0;
	protected:
		IndexBuffer() = default;
	};
}
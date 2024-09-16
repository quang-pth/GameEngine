#pragma once

#include"pch.h"
#include"Core/Type/Object.h"
#include"Renderer/RendererAPI.h"

namespace VIEngine {
	class VI_API IndexBuffer : public Object {
	public:
		DECLARE_RTTI
	public:
		static IndexBuffer* Create();
	public:
		virtual ~IndexBuffer() = default;
		virtual void Release() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetID() const = 0;
		virtual uint32_t GetSize() const = 0;
		virtual uint32_t GetNums() const = 0;
		virtual void SetData(void* data, uint32_t size, uint32_t nums, ERendererMode mode = ERendererMode::Static) = 0;
	protected:
		IndexBuffer() = default;

	};
}
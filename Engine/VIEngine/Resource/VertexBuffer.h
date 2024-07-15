#pragma once

#include"pch.h"
#include"Math/Math.h"
#include"Core/Type/Object.h"

namespace VIEngine {
	struct Vertex {
		Math::Vector3 Position;
		Math::Vector2 TextureCoords;
		Math::Vector3 Color;
	};

	class VI_API VertexBuffer : public Object {
	public:
		DECLARE_RTTI
	public:
		virtual ~VertexBuffer() = default;
		virtual uint32_t GetID() const = 0;
		virtual uint32_t GetSize() const = 0;
		virtual uint32_t GetStride() const = 0;
		virtual const void* GetData() const = 0;
		virtual void SetData(const void*, uint32_t) = 0;
	protected:
		VertexBuffer() = default;
	};
}
#pragma once

#include"pch.h"
#include"Core/Type/Object.h"
#include"Renderer/RendererAPI.h"
#include<glm/glm.hpp>

namespace VIEngine {
	struct VI_API Vertex {
		glm::vec3 Position;
		glm::vec2 TextureCoords;
		glm::vec4 Color;
	};

	class VI_API VertexBuffer : public Object {
	public:
		DECLARE_RTTI
	public:
		static VertexBuffer* Create();
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetID() = 0;
		virtual uint32_t GetSize() = 0;
		virtual void SetData(void* data, uint32_t size, ERendererMode mode = ERendererMode::Static) = 0;

	protected:
		VertexBuffer() = default;
	};
}
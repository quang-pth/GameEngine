#pragma once

#include"Core/Type/Object.h"
#include"Renderer/RendererAPI.h"
#include<glm/glm.hpp>

namespace VIEngine {
	struct VI_API Vertex {
		glm::vec3 Position;
		glm::vec2 TexCoords;
		glm::vec4 Color;
	};

	class VI_API VertexBuffer : public Object {
	public:
		DECLARE_RTTI
	public:
		static VertexBuffer* Create();
	public:
		virtual ~VertexBuffer() = default;
		virtual void Release() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetID() const = 0;
		virtual uint32_t GetSize() const = 0;
		virtual void SetID(uint32_t id) = 0;
		virtual void SetSize(uint32_t size) = 0;
	protected:
		VertexBuffer() = default;
	};
}
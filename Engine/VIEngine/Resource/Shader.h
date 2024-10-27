#pragma once

#include"Core/Type/Object.h"
#include<glm/glm.hpp>

namespace VIEngine {
	class VI_API Shader : public Object {
	public:
		DECLARE_RTTI
	public:
		static Shader* Create(const std::string& filepath);
	public:
		virtual ~Shader() = default;
		virtual void Release() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetID() const = 0;
		virtual const std::string& GetName() const = 0;
		virtual void SetBool(const std::string& name, bool value) = 0;
		virtual void SetInt(const std::string& name, int32_t value) = 0;
		virtual void SetInts(const std::string& name, int32_t* value, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloats(const std::string& name, float* value, uint32_t count) = 0;
		virtual void SetFloats2(const std::string& name, float* value, uint32_t count) = 0;
		virtual void SetVector2(const std::string& name, float x, float y) = 0;
		virtual void SetVector2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetVector3(const std::string& name, float x, float y, float z) = 0;
		virtual void SetVector3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetMatrix4(const std::string& name, const glm::mat4& value) = 0;
	protected:
		Shader() = default;
	};
}
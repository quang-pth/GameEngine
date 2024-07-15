#pragma once

#include"pch.h"
#include"Core/Type/Object.h"
#include"Math/Math.h"

namespace VIEngine {
	class VI_API Shader : public Object {
	public:
		DECLARE_RTTI
	public:
		virtual ~Shader() = default;
		virtual uint32_t GetID() const = 0;
        virtual void SetBool(const std::string& name, bool value) = 0;
        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetInts(const std::string& name, int32_t* value, uint32_t count) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloats(const std::string& name, float* value, uint32_t count) = 0;
        virtual void SetFloats2(const std::string& name, float* value, uint32_t count) = 0;
        virtual void SetVector2(const std::string& name, float x, float y) = 0;
        virtual void SetVector2(const std::string& name, const Math::Vector2& value) = 0;
        virtual void SetVector3(const std::string& name, float x, float y, float z) = 0;
        virtual void SetVector3(const std::string& name, const Math::Vector3& value) = 0;
        virtual void SetMatrix4(const std::string& name, const Math::Matrix4& value) = 0;
	protected:
		Shader() = default;
	};
}
#pragma once

#include"Resource/Resource.h"
#include"Renderer/API/RendererAPI.h"

namespace VIEngine {
	class OpenGLShader : public Shader {
	public:
		DECLARE_RTTI
	public:
		OpenGLShader();
		OpenGLShader(const char* vertexSource, const char* fragmentSource);
		~OpenGLShader();

		VI_FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		virtual void SetBool(const std::string& name, bool value) override;
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetInts(const std::string& name, int32_t* value, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloats(const std::string& name, float* value, uint32_t count) override;
		virtual void SetFloats2(const std::string& name, float* value, uint32_t count) override;
		virtual void SetVector2(const std::string& name, float x, float y) override;
		virtual void SetVector2(const std::string& name, const Math::Vector2& value) override;
		virtual void SetVector3(const std::string& name, float x, float y, float z) override;
		virtual void SetVector3(const std::string& name, const Math::Vector3& value) override;
		virtual void SetMatrix4(const std::string& name, const Math::Matrix4& value) override;
	private:
		bool IsValidShader(uint32_t shaderID, EShaderType shaderType);
	private:
		uint32_t mID;
	};
}
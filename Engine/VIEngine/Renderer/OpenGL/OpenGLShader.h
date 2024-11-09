#pragma once

#include"Resource/Shader.h"
#include"Renderer/RendererAPI.h"

namespace VIEngine {
	class OpenGLShader : public Shader {
	public:
		DECLARE_RTTI
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();
		virtual void Release() override;
		virtual void Bind() override;
		virtual void Unbind() override;
		VI_FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		VI_FORCE_INLINE virtual const std::string& GetName() const override { return mName; }
		virtual void SetBool(const std::string& name, bool value) override;
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetInts(const std::string& name, int* value, int count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloats(const std::string& name, float* value, int count) override;
		virtual void SetFloats2(const std::string& name, float* value, int count) override;
		virtual void SetVector2(const std::string& name, float x, float y) override;
		virtual void SetVector2(const std::string& name, const glm::vec2& value) override;
		virtual void SetVector3(const std::string& name, float x, float y, float z) override;
		virtual void SetVector3(const std::string& name, const glm::vec3& value) override;
		virtual void SetMatrix4(const std::string& name, const glm::mat4& value) override;
	private:
		bool IsValidShader(uint32_t shaderID, ERendererResource resource);
	private:
		uint32_t mID;
		std::string mName, mVertexSource, mFragmentSource;
	};
}
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
	private:
		bool IsValidShader(uint32_t shaderID, EShaderType shaderType);
	private:
		uint32_t mID;
	};
}
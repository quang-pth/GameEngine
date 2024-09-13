#include"OpenGLShader.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"Core/Type/Cast.h"

#include<glad/gl.h>
#include<glm/gtc/type_ptr.hpp>

namespace VIEngine {
	DEFINE_RTTI(OpenGLShader, Shader::RunTimeType)

	OpenGLShader::OpenGLShader(const char* name, const char* vertexSource, const char* fragmentSource) : mID(), mName(name), mVertexSource(vertexSource), mFragmentSource(fragmentSource) {
		//strcpy(mVertexSource, vertexSource);
		//strcpy(mFragmentSource, fragmentSource);
		
		Renderer::Submit([this]() {
			uint32_t vertexShader, fragmentShader;
			const char* vertexSource = mVertexSource.c_str();
			const char* fragmentSource = mFragmentSource.c_str();
			// Vertex shader
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexSource, nullptr);
			glCompileShader(vertexShader);
			bool vertexCompiledSuccess = IsValidShader(vertexShader, ERendererResource::FragmentShader);
			// Fragment Shader
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
			glCompileShader(fragmentShader);
			bool fragmentCompiledSuccess = IsValidShader(fragmentShader, ERendererResource::VertexShader);
			// Shader program
			mID = glCreateProgram();
			if (vertexCompiledSuccess && fragmentCompiledSuccess) {
				glAttachShader(mID, vertexShader);
				glAttachShader(mID, fragmentShader);
			}
			glLinkProgram(mID);
			if (IsValidShader(mID, ERendererResource::ShaderProgram)) {
				CORE_LOG_INFO("Loaded shader {0} with id {1} successfully", mName.c_str(), mID);
			}
			// Free shaders
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		});
	}

	OpenGLShader::~OpenGLShader() {
		Renderer::Submit([this]() {
			glDeleteShader(mID);
			ResourceManager::Get().FreeShader(this);
		});
	}

	void OpenGLShader::Bind() {
		Renderer::Submit([this]() {
			glUseProgram(mID);
		});
	}

	void OpenGLShader::Unbind() {
		Renderer::Submit([]() {
			glUseProgram(0);
		});
	}

	void OpenGLShader::SetBool(const std::string& name, bool value)
	{
		Renderer::Submit([name, value, this]() {
			glUniform1i(glGetUniformLocation(mID, name.c_str()), StaticCast<int>(value));
		});
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		Renderer::Submit([name, value, this]() {
			glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
		});
	}

	void OpenGLShader::SetInts(const std::string& name, int32_t* value, uint32_t count)
	{
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		Renderer::Submit([name, value, this]() {
			glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
		});
	}

	void OpenGLShader::SetFloats(const std::string& name, float* value, uint32_t count)
	{
	}

	void OpenGLShader::SetFloats2(const std::string& name, float* value, uint32_t count)
	{
	}

	void OpenGLShader::SetVector2(const std::string& name, float x, float y)
	{
	}

	void OpenGLShader::SetVector2(const std::string& name, const glm::vec2& value)
	{
	}

	void OpenGLShader::SetVector3(const std::string& name, float x, float y, float z)
	{
	}

	void OpenGLShader::SetVector3(const std::string& name, const glm::vec3& value)
	{
		Renderer::Submit([name, value, this]() {
			glUniform3fv(glGetUniformLocation(mID, name.c_str()), 1, glm::value_ptr(value));
		});
	}

	void OpenGLShader::SetMatrix4(const std::string& name, const glm::mat4& value)
	{
	}

	bool OpenGLShader::IsValidShader(uint32_t shaderID, ERendererResource shaderType) {
		int success;
		char infoLog[512];

		switch (shaderType)
		{
		case ERendererResource::VertexShader:
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Vertex shader", infoLog);
				return false;
			}
			return true;
			break;
		case ERendererResource::FragmentShader:
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Fragment shader", infoLog);
				return false;
			}
			return true;
			break;
		case ERendererResource::ShaderProgram:
			glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shaderID, 512, nullptr, infoLog);
				CORE_LOG_ERROR("Shader Program compiled failed: {0}", infoLog);
				return false;
			}
			return true;
			break;
		default:
			CORE_LOG_WARN("Invalid shader type specified");
			return false;
		}
	}
}
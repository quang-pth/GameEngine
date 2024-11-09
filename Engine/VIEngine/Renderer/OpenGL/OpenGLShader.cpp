#include"OpenGLShader.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"Core/Type/Cast.h"
#include"Core/Logger/Logger.h"

#include<glad/gl.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace VIEngine {
	DEFINE_RTTI(OpenGLShader, Shader::RunTimeType)

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : 
		mName(name), mVertexSource(vertexSource), mFragmentSource(fragmentSource)
	{
		Renderer::Submit([this]() {
			uint32_t vertexShaderID, fragmentShaderID;
			const char* vertexSource = mVertexSource.c_str();
			const char* fragmentSource = mFragmentSource.c_str();
			// Vertex Shader
			vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShaderID, 1, &vertexSource, nullptr);
			glCompileShader(vertexShaderID);
			// Fragment Shader
			fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShaderID, 1, &fragmentSource, nullptr);
			glCompileShader(fragmentShaderID);
			// Shader Program
			mID = glCreateProgram();
			if (
				IsValidShader(vertexShaderID, ERendererResource::VertexShader) &&
				IsValidShader(fragmentShaderID, ERendererResource::FragmentShader)
			) {
				glAttachShader(mID, vertexShaderID);
				glAttachShader(mID, fragmentShaderID);
				glLinkProgram(mID);
			
				if (IsValidShader(mID, ERendererResource::Shader)) {
					CORE_LOG_INFO("Shader program {0} with id {1} is loaded!", mName.c_str(), mID);
				}
			}
			
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
		});
	}

	OpenGLShader::~OpenGLShader()
	{
	}

	void OpenGLShader::Release() {
		Renderer::Submit([this]() {
			glDeleteShader(mID);
			ResourceManager::Get().FreeShader(this);
		});
	}

	void OpenGLShader::Bind()
	{
		Renderer::Submit([this]() {
			glUseProgram(mID);
		});
	}

	void OpenGLShader::Unbind()
	{
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

	void OpenGLShader::SetInts(const std::string& name, int* value, int count)
	{
		Renderer::Submit([name, value, count, this]() {
			glUniform1iv(glGetUniformLocation(mID, name.c_str()), count, value);
		});
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		Renderer::Submit([name, value, this]() {
			glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
		});
	}

	void OpenGLShader::SetFloats(const std::string& name, float* value, int count)
	{
		Renderer::Submit([name, value, count, this]() {
			glUniform1fv(glGetUniformLocation(mID, name.c_str()), count, value);
		});
	}

	void OpenGLShader::SetFloats2(const std::string& name, float* value, int count)
	{
		Renderer::Submit([name, value, count, this]() {
			glUniform2fv(glGetUniformLocation(mID, name.c_str()), count, value);
		});
	}

	void OpenGLShader::SetVector2(const std::string& name, float x, float y)
	{
		Renderer::Submit([name, x, y, this]() {
			glUniform2f(glGetUniformLocation(mID, name.c_str()), x, y);
		});
	}

	void OpenGLShader::SetVector2(const std::string& name, const glm::vec2& value)
	{
		Renderer::Submit([name, value, this]() {
			glUniform2fv(glGetUniformLocation(mID, name.c_str()), 1, glm::value_ptr(value));
		});
	}

	void OpenGLShader::SetVector3(const std::string& name, float x, float y, float z)
	{
		Renderer::Submit([name, x, y, z, this]() {
			glUniform3f(glGetUniformLocation(mID, name.c_str()), x, y, z);
		});
	}

	void OpenGLShader::SetVector3(const std::string& name, const glm::vec3& value)
	{
		Renderer::Submit([name, value, this]() {
			glUniform3fv(glGetUniformLocation(mID, name.c_str()), 1, glm::value_ptr(value));
		});
	}

	void OpenGLShader::SetMatrix4(const std::string& name, const glm::mat4& value)
	{
		Renderer::Submit([name, value, this]() {
			glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		});
	}
	
	bool OpenGLShader::IsValidShader(uint32_t shaderID, ERendererResource resource) {
		int32_t success;
		char info[512];

		switch (resource)
		{
		case VIEngine::ERendererResource::VertexShader:
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, 512, nullptr, info);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Vertex Shader", info);
				return false;
			}
			break;
		case VIEngine::ERendererResource::FragmentShader:
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, 512, nullptr, info);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Fragment Shader", info);
				return false;
			}
			break;
		case VIEngine::ERendererResource::Shader:
			glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shaderID, 512, nullptr, info);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Shader Program", info);
				return false;
			}
			break;
		default:
			CORE_LOG_WARN("Invalid resource");
			break;
		}

		return true;
	}
}
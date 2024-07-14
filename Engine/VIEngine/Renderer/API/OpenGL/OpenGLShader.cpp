#include"OpenGLShader.h"
#include"Core/Logger/Logger.h"
#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI(OpenGLShader, &Shader::RunTimeType)

	OpenGLShader::OpenGLShader() {

	}

	OpenGLShader::OpenGLShader(const char* vertexSource, const char* fragmentSource) {
        uint32_t vertexShader, fragmentShader;
        // Vertex shader
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(vertexShader);
        bool vertexCompiledSuccess = IsValidShader(vertexShader, EShaderType::VERTEX);
        // Fragment Shader
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragmentShader);
        bool fragmentCompiledSuccess = IsValidShader(fragmentShader, EShaderType::FRAGMENT);
        // Shader program
        mID = glCreateProgram();
        if (vertexCompiledSuccess && fragmentCompiledSuccess) {
            glAttachShader(mID, vertexShader);
            glAttachShader(mID, fragmentShader);
        }
        glLinkProgram(mID);
        IsValidShader(mID, EShaderType::PROGRAM);
        // Free shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteShader(mID);
	}

    bool OpenGLShader::IsValidShader(uint32_t shaderID, EShaderType shaderType) {
        int success;
        char infoLog[512];

        switch (shaderType)
        {
        case EShaderType::VERTEX:
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
                CORE_LOG_ERROR("{0} compiled failed: {1}", "Vertex shader", infoLog);
                return false;
            }
            return true;
            break;
        case EShaderType::FRAGMENT:
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
                CORE_LOG_ERROR("{0} compiled failed: {1}", "Fragment shader", infoLog);
                return false;
            }
            return true;
            break;
        case EShaderType::PROGRAM:
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
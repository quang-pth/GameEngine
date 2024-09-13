#include"Shader.h"
#include"ResourceManager.h"
#include"Renderer/OpenGL/OpenGLShader.h"

namespace VIEngine {
	DEFINE_RTTI(Shader, Object::RunTimeType)

	Shader* Shader::Create(const char* filepath) {
		return ResourceManager::Get().NewShader(filepath);
	}
}
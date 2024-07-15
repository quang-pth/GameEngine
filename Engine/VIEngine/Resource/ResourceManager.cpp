#include"ResourceManager.h"
#include"Shader.h"
#include"Core/Application.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
	ResourceManager& ResourceManager::Get() {
		static ResourceManager* resourceManager = Application::Get().GetGlobalMemoryUsage().NewOnStack<ResourceManager>("ResourceManager");
		return *resourceManager;
	}

	Shader* ResourceManager::GetShader(const char* filepath) {
		if (mShaderMap.find(filepath) != mShaderMap.end()) {
			return mShaderMap.at(filepath);
		}

		return nullptr;
	}

	void ResourceManager::SaveShader(const char* filepath, Shader* shader) {
		if (mShaderMap.find(filepath) != mShaderMap.end()) {
			CORE_LOG_WARN("Shader {0} is already saved!", filepath);
			return;
		}

		CORE_LOG_TRACE("Shader {0} is loaded successfully with ID {1}", filepath, shader->GetID());
		mShaderMap[filepath] = shader;
	}

	std::unordered_map<std::string, std::string> ResourceManager::ParseSourceGLSL(const char* filepath) {
		std::string source = ReadFile(filepath);
		std::unordered_map<std::string, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			VI_ASSERT(eol != std::string::npos, "Syntax error");
			
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			VI_ASSERT((type == "vertex" || type == "fragment" || type == "pixel") && "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[type] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	std::string ResourceManager::ReadFile(const char* filepath) {
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			CORE_LOG_WARN("Could not read shader file {0}", filepath);
		}
		return result;
	}
}
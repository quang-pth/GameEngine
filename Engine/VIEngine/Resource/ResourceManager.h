#pragma once

#include"pch.h"
#include"Memory/MemoryManager.h"

namespace VIEngine {
	class Shader;
	
	class ResourceManager : public MemoryManager {
		friend class MemoryManager;
	public:
		virtual ~ResourceManager() = default;
	public:
		static ResourceManager& Get();
	public:
		Shader* GetShader(const char* filepath);
		void SaveShader(const char* filepath, Shader*);
		std::unordered_map<std::string, std::string> ParseSourceGLSL(const char* filepath);
		std::string ReadFile(const char* filepath);

	private:
		std::unordered_map<const char*, Shader*> mShaderMap;

	private:
		ResourceManager() = default;
	};
}
#include"OpenGLResourceManager.h"
#include"Core/Type/Cast.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(OpenGLResourceManager)

	OpenGLResourceManager::OpenGLResourceManager() :
		mVertexBufferManager("OpenGLVertexBufferManager"), mIndexBufferManager("OpenGLIndexBufferManager"), 
		mShaderBufferManager("OpenGLShaderBufferManager") {

	}

	OpenGLResourceManager::~OpenGLResourceManager() {

	}

	void OpenGLResourceManager::OnReset() {
		mVertexBufferManager.Reset();
		mIndexBufferManager.Reset();
		mShaderBufferManager.Reset();
	}

	VertexBuffer* OpenGLResourceManager::NewVertexBuffer() {
		return mVertexBufferManager.NewObject();
	}
	
	void OpenGLResourceManager::FreeVertexBuffer(void* memory) {
		mVertexBufferManager.FreeObject(memory);
	}
	IndexBuffer* OpenGLResourceManager::NewIndexBuffer() {
		return mIndexBufferManager.NewObject();
	}
	
	void OpenGLResourceManager::FreeIndexBuffer(void* memory) {
		mIndexBufferManager.FreeObject(memory);
	}

	Shader* OpenGLResourceManager::NewShader(const char* filepath) {
		if (mShaderMap.count(filepath)) {
			return mShaderMap.at(filepath);
		}

		auto shaderSources = ParseGLSL(filepath);
		
		OpenGLShader* shader = mShaderBufferManager.NewObject(filepath, shaderSources["vertex"].c_str(), shaderSources["fragment"].c_str());
		mShaderMap[filepath] = shader;
		return shader;
	}

	void OpenGLResourceManager::FreeShader(void* memory) {
		mShaderBufferManager.FreeObject(memory);
		mShaderMap.erase(StaticCast<Shader*>(memory)->GetName());
	}

	void* OpenGLResourceManager::AllocatePerFrame(uint32_t size, uint8_t alignment) {
		return mGeneralMemoryManager.AllocatePerFrame(size, alignment);
	}

	std::unordered_map<std::string, std::string> OpenGLResourceManager::ParseGLSL(const char* shaderSource) {
		std::string source = Read(shaderSource);
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
			VI_ASSERT((type == "vertex" || type == "fragment") && "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[type] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	std::string OpenGLResourceManager::Read(const char* filepath) {
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
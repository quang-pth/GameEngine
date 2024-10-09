#include"OpenGLResourceManager.h"
#include"Core/Type/Cast.h"

#include<stb/stb_image.h>

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(OpenGLResourceManager)

	OpenGLResourceManager::OpenGLResourceManager() : 
		mVertexArrayMemoryManager("VertexArrayMemoryManager"),
		mVertexBufferMemoryManager("VertexBufferMemoryManager"),
		mIndexBufferMemoryManager("IndexBufferMemoryManager"),
		mShaderMemoryManager("ShaderMemoryManager"),
		mTexture2DMemoryManager("Texture2DMemoryManager")
	{

	}

	OpenGLResourceManager::~OpenGLResourceManager()
	{

	}

	void OpenGLResourceManager::OnReset()
	{
		mVertexArrayMemoryManager.Reset();
		mVertexBufferMemoryManager.Reset();
		mIndexBufferMemoryManager.Reset();
		mShaderMemoryManager.Reset();
		mTexture2DMemoryManager.Reset();
	}

	VertexArray* OpenGLResourceManager::NewVertexArray()
	{
		return mVertexArrayMemoryManager.NewObject();
	}

	void OpenGLResourceManager::FreeVertexArray(VertexArray* memory)
	{
		mVertexArrayMemoryManager.FreeObject(memory);
	}

	VertexBuffer* OpenGLResourceManager::NewVertexBuffer()
	{
		return mVertexBufferMemoryManager.NewObject();
	}

	void OpenGLResourceManager::FreeVertexBuffer(VertexBuffer* memory)
	{
		mVertexBufferMemoryManager.FreeObject(memory);
	}

	IndexBuffer* OpenGLResourceManager::NewIndexBuffer()
	{
		return mIndexBufferMemoryManager.NewObject();
	}

	void OpenGLResourceManager::FreeIndexBuffer(IndexBuffer* memory)
	{
		mIndexBufferMemoryManager.FreeObject(memory);
	}

	Shader* OpenGLResourceManager::NewShader(const char* filepath)
	{
		if (mShaderMap.count(filepath)) {
			return mShaderMap.at(filepath);
		}

		auto shaderSources = ParseGLSL(filepath);
		OpenGLShader* shader = mShaderMemoryManager.NewObject(filepath, shaderSources["vertex"].c_str(), shaderSources["fragment"].c_str());
		mShaderMap[filepath] = shader;
		return shader;
	}

	void OpenGLResourceManager::FreeShader(Shader* memory)
	{
		mShaderMemoryManager.FreeObject(memory);
		mShaderMap.erase(memory->GetName());
	}

	void* OpenGLResourceManager::AllocatePerFrame(uint32_t size, uint8_t alignment)
	{
		return mGeneralMemoryManager.AllocatePerFrame(size, alignment);
	}

	Texture2D* OpenGLResourceManager::NewTexture2D(const std::string& filepath, bool alpha)
	{
		if (mTexture2DMap.count(filepath.c_str()) > 0) {
			return mTexture2DMap.at(filepath.c_str());
		}

		Texture2D* texture2D = mTexture2DMemoryManager.NewObject(filepath.c_str(), alpha);
		mTexture2DMap[filepath.c_str()] = texture2D;

		return texture2D;
	}

	void OpenGLResourceManager::FreeTexture2D(Texture2D* memory)
	{
		auto& textureData = memory->GetTextureData();
		if (textureData.Data) {
			CORE_LOG_WARN("Image {0} is not free before get released in resouce manager, possible memory leaks detected", textureData.Name);
			FreeImageData(textureData.Data);
		}
		mTexture2DMemoryManager.FreeObject(memory);
		mTexture2DMap.erase(memory->GetName());
	}

	std::unordered_map<std::string, std::string> OpenGLResourceManager::ParseGLSL(const char* shaderSource)
	{
		std::string source = ReadFromFile(shaderSource);
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

	std::string OpenGLResourceManager::ReadFromFile(const char* filepath)
	{
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

	TextureData OpenGLResourceManager::LoadImageFromFile(const char* filepath, bool alpha) {
		TextureData textureData;
		textureData.Alpha = alpha;
		textureData.Name = filepath;

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);

		void* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
		if (data) {
			textureData.Width = width;
			textureData.Height= height;
			textureData.NumberOfChannels = nrChannels;
			textureData.Data = data;

			ETextureFormat format;
			if (nrChannels == 1) {
				format = ETextureFormat::RED;
			}
			else if (nrChannels == 3) {
				format = ETextureFormat::RGB;
			}
			else {
				format = ETextureFormat::RGBA;
			}
			textureData.InternalFormat = format;
			textureData.ImageFormat = format;

			CORE_LOG_INFO("Texture {0} loaded successfully", filepath);
		}
		else {
			CORE_LOG_TRACE("====================TEXTURE==================");
			CORE_LOG_ERROR("Width: {0}", width);
			CORE_LOG_ERROR("Height: {0}", height);
			CORE_LOG_ERROR("Channels: {0}", nrChannels);
			CORE_LOG_ERROR("Failed to load texture: {0}", stbi_failure_reason());
			CORE_LOG_TRACE("====================TEXTURE==================");
		}

		stbi_set_flip_vertically_on_load(false);

		return textureData;
	}

	void OpenGLResourceManager::FreeImageData(void* data) {
		if (data == nullptr) return;

		stbi_image_free(data);
	}
}
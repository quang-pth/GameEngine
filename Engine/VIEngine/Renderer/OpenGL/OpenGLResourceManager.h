#pragma once

#include"Core/Type/RTTI.h"
#include"Resource/ResourceManager.h"
#include"Memory/MemoryChunkManager.h"
#include"OpenGLVertexArray.h"
#include"OpenGLVertexBuffer.h"
#include"OpenGLIndexBuffer.h"
#include"OpenGLShader.h"
#include"OpenGLTexture2D.h"

namespace VIEngine {
	class OpenGLResourceManager : public ResourceManager {
	public:
		DECLARE_RTTI

	public:
		OpenGLResourceManager();
		~OpenGLResourceManager();

		virtual void OnReset() override;
		virtual VertexArray* NewVertexArray() override;
		virtual void FreeVertexArray(VertexArray* memory) override;
		virtual class VertexBuffer* NewVertexBuffer() override;
		virtual void FreeVertexBuffer(class VertexBuffer* memory) override;
		virtual class IndexBuffer* NewIndexBuffer() override;
		virtual void FreeIndexBuffer(class IndexBuffer* memory) override;
		virtual class Shader* NewShader(const std::string& filepath) override;
		virtual void FreeShader(class Shader* memory) override;
		virtual void* AllocatePerFrame(uint32_t size, uint8_t alignment) override;
		virtual class Texture2D* NewTexture2D(const std::string& filepath, bool alpha) override;
		virtual void FreeTexture2D(class Texture2D* memory) override;
		virtual TextureData LoadImageFromFile(const std::string& filepath, bool alpha = true) override;
		virtual void FreeImageData(void* data) override;
	private:
		std::unordered_map<std::string, std::string> ParseGLSL(const std::string& shaderSource);
		std::string ReadFromFile(const std::string& filepath);
	private:
		MemoryManager mGeneralMemoryManager;
		MemoryChunkManager<OpenGLVertexArray, 100> mVertexArrayMemoryManager;
		MemoryChunkManager<OpenGLVertexBuffer, 100> mVertexBufferMemoryManager;
		MemoryChunkManager<OpenGLIndexBuffer, 100> mIndexBufferMemoryManager;
		MemoryChunkManager<OpenGLShader, 100> mShaderMemoryManager;
		MemoryChunkManager<OpenGLTexture2D, 100> mTexture2DMemoryManager;
		std::unordered_map<std::string, OpenGLShader*> mShaderMap;
		std::unordered_map<std::string, Texture2D*> mTexture2DMap;
	};
}
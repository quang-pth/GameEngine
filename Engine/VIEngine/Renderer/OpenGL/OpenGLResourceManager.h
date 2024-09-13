#pragma once

#include"Resource/ResourceManager.h"
#include"OpenGLVertexBuffer.h"
#include"OpenGLIndexBuffer.h"
#include"OpenGLShader.h"
#include"Core/Type/RTTI.h"

namespace VIEngine {
	class OpenGLResourceManager : public ResourceManager {
	public:
		DECLARE_RTTI
	
	public:
		OpenGLResourceManager();
		~OpenGLResourceManager();
		virtual void OnReset() override;
		virtual class VertexBuffer* NewVertexBuffer() override;
		virtual void FreeVertexBuffer(void* memory) override;
		virtual class IndexBuffer* NewIndexBuffer() override;
		virtual void FreeIndexBuffer(void* memory) override;
		virtual class Shader* NewShader(const char* filepath) override;
		virtual void FreeShader(void* memory) override;
		virtual void* AllocatePerFrame(uint32_t size, uint8_t alignment) override;
	private:
		std::unordered_map<std::string, std::string> ParseGLSL(const char* shaderSource);
		std::string Read(const char* filepath);
	private:
		MemoryManager mGeneralMemoryManager;
		MemoryChunkManager<OpenGLVertexBuffer, 100> mVertexBufferManager;
		MemoryChunkManager<OpenGLIndexBuffer, 100> mIndexBufferManager;
		MemoryChunkManager<OpenGLShader, 100> mShaderBufferManager;
		std::unordered_map<const char*, OpenGLShader*> mShaderMap;
	};
}
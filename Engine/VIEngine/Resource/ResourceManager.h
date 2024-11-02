#pragma once

#include"pch.h"
#include"Renderer/RendererAPI.h"
#include"Texture2D.h"
#include"Memory/MemoryChunkManager.h"
#include"Sprite.h"

namespace VIEngine {
	class VI_API ResourceManager {
	public:
		static ResourceManager& Get();
		static void OnInit(ERendererSpec rendererSpec);
		static void OnShutdown();
	private:
		static ResourceManager* sInstance;

	public:
		virtual ~ResourceManager() = default;

		virtual void OnReset();
		virtual class VertexArray* NewVertexArray(bool useBatchVertex) = 0;
		virtual void FreeVertexArray(class VertexArray* memory) = 0;
		virtual class VertexBuffer* NewVertexBuffer() = 0;
		virtual void FreeVertexBuffer(class VertexBuffer* memory) = 0;
		virtual class IndexBuffer* NewIndexBuffer() = 0;
		virtual void FreeIndexBuffer(class IndexBuffer* memory) = 0;
		virtual class Shader* NewShader(const std::string& filepath) = 0;
		virtual void FreeShader(class Shader* memory) = 0;
		virtual void* AllocatePerFrame(uint32_t size, uint8_t alignment) = 0;
		virtual void* AllocateOnStack(const std::string& usage, uint32_t size, uint8_t alignment) = 0;
		virtual class Texture2D* NewTexture2D(const std::string& filepath, bool alpha) = 0;
		virtual void FreeTexture2D(class Texture2D* memory) = 0;
		virtual TextureData LoadImageFromFile(const std::string& filepath, bool alpha = true) = 0;
		virtual void FreeImageData(void* data) = 0;
		Sprite* NewSprite(const std::string& filepath);
		void FreeSprite(Sprite* sprite);
	protected:
		ResourceManager();
	private:
		MemoryChunkManager<Sprite, 100> mSpriteMemoryManager;
	};
}
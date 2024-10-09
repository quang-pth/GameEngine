#pragma once

#include"pch.h"
#include"Renderer/RendererAPI.h"
#include"Texture2D.h"

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

		virtual void OnReset() = 0;
		virtual class VertexArray* NewVertexArray() = 0;
		virtual void FreeVertexArray(class VertexArray* memory) = 0;
		virtual class VertexBuffer* NewVertexBuffer() = 0;
		virtual void FreeVertexBuffer(class VertexBuffer* memory) = 0;
		virtual class IndexBuffer* NewIndexBuffer() = 0;
		virtual void FreeIndexBuffer(class IndexBuffer* memory) = 0;
		virtual class Shader* NewShader(const char* filepath) = 0;
		virtual void FreeShader(class Shader* memory) = 0;
		virtual void* AllocatePerFrame(uint32_t size, uint8_t alignment) = 0;
		virtual class Texture2D* NewTexture2D(const std::string& filepath, bool alpha) = 0;
		virtual void FreeTexture2D(class Texture2D* memory) = 0;
		virtual TextureData LoadImageFromFile(const char* filepath, bool alpha = true) = 0;
		virtual void FreeImageData(void* data) = 0;
	protected:
		ResourceManager() = default;
	};
}
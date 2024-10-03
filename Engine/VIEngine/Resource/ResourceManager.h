#pragma once

#include"pch.h"
#include"Renderer/RendererAPI.h"

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
		virtual void FreeVertexBuffer(void* memory) = 0;
		virtual class IndexBuffer* NewIndexBuffer() = 0;
		virtual void FreeIndexBuffer(void* memory) = 0;
		virtual class Shader* NewShader(const char* filepath) = 0;
		virtual void FreeShader(void* memory) = 0;
		virtual void* AllocatePerFrame(uint32_t size, uint8_t alignment) = 0;
	protected:
		ResourceManager() = default;
	};
}
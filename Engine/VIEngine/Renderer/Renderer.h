#pragma once

#include"pch.h"
#include"Memory/MemoryManager.h"
#include"RenderCommand.h"
#include"API/RendererAPIFactory.h"

namespace VIEngine {
	class VI_API Renderer : public MemoryManager {
	public:
		Renderer();
		~Renderer();

		void OnInit(ERendererAPI api = ERendererAPI::OpenGL);
		void OnShutdown();

		void Submit(const RenderCommandCallback& commandCallback);

		void BindVertexBufferImpl(const VertexBuffer* vertexBuffer);
		void UnbindVertexBufferImpl(const VertexBuffer* vertexBuffer);
		
		void BindIndexBufferImpl(const IndexBuffer* indexBuffer);
		void UnbindIndexBufferImpl(const IndexBuffer* indexBuffer);

		void BindShaderImpl(const Shader* shader);
		void UnbindShaderImpl(const Shader* shader);
	
		void BeginScene();
		void Render();
		void EndScene();
	private:
		std::queue<RenderCommand*> mCommandQueue;
		Shared<RendererAPI> mRendererAPI;
	};
}

#define RENDER_COMMAND(cmd) [this]() { cmd }
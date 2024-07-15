#pragma once

#include"pch.h"
#include"RenderCommand.h"
#include"API/RendererAPIFactory.h"
#include"Memory/MemoryManager.h"

namespace VIEngine {
	class VI_API Renderer : protected MemoryManager {
	public:
		Renderer();
		~Renderer();

		void OnInit(ERendererAPI api = ERendererAPI::OpenGL);
		void OnShutdown();

		void Submit(const RenderCommandCallback& commandCallback);

		void BeginScene();
		void Render();
		void EndScene();
	private:
		std::vector<RenderCommand*> mCommandQueue;
		Shared<RendererAPI> mRendererAPI;
	};
}


#define RENDER_COMMAND(...) [this]() { __VA_ARGS__ }
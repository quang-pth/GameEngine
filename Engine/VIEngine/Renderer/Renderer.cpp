#include"Renderer.h"

#include"Core/Logger/Logger.h"

namespace VIEngine {
	Renderer::Renderer() : MemoryManager() {

	}

	Renderer::~Renderer() {
	}

	void Renderer::OnInit(ERendererAPI api) {
		mRendererAPI.reset(RendererAPIFactory::CreateRendererAPI(api));
		VI_ASSERT(mRendererAPI != nullptr && "Failed to init renderer");
		mRendererAPI->OnInit();
	}

	void Renderer::OnShutdown() {
		mRendererAPI->OnShutdown();
	}

	void Renderer::Submit(const RenderCommandCallback& commandCallback)
	{
		RenderCommand* command = NewPerFrame<RenderCommand>(commandCallback);
		mCommandQueue.emplace_back(command);
		//CORE_LOG_TRACE("Command is allocated at address {0}", (void*)command);
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::Render()
	{
		for (auto renderCommand : mCommandQueue) {
			renderCommand->Execute();
		}
	}

	void Renderer::EndScene()
	{
		mCommandQueue.clear();
	}
}
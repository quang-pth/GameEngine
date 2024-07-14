#include"Renderer.h"

#include"Core/Logger/Logger.h"

namespace VIEngine {
	Renderer::Renderer() : MemoryManager() {

	}

	Renderer::~Renderer() {
	}

	void Renderer::OnInit(ERendererAPI api) {
		mRendererAPI.reset(RendererAPIFactory::CreateRendererAPI(api));
		mRendererAPI->OnInit();
	}

	void Renderer::OnShutdown() {
		mRendererAPI->OnShutdown();
	}

	void Renderer::Submit(const RenderCommandCallback& commandCallback)
	{
		RenderCommand* command = NewPerFrame<RenderCommand>(commandCallback);
		mCommandQueue.push(command);
		//CORE_LOG_TRACE("Command is allocated at address {0}", (void*)command);
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::Render()
	{
		while (!mCommandQueue.empty()) {
			mCommandQueue.front()->Execute();
			mCommandQueue.pop();
		}
	}

	void Renderer::EndScene()
	{
	}
}
#include"Renderer.h"
#include"Core/Logger/Logger.h"
#include"RenderCommand.h"
#include"RenderCommandQueue.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(Renderer)

	void Renderer::Submit(const RenderCallback& renderCallback) {
		if (Application::Get().GetPerFrameData().IsCatchUpUpdate) return;

		RenderCommandQueue::Enqueue(renderCallback);
	}

	void Renderer::ClearColor(float r, float g, float b, float w) {
		Submit([r, g, b, w]() {
			RenderCommand::ClearColor(r, g, b, w);
		});
	}

	Renderer::Renderer() {
		
	}

	Renderer::~Renderer() {

	}

	void Renderer::OnInit(const ApplicationConfiguration& appConfig) {
		Submit([appConfig]() {
			RenderCommand::OnInit(appConfig.RendererSpec);
		});
	}

	bool Renderer::BeginScene() {
		return true;
	}

	void Renderer::Render() {
		RenderCommandQueue::ProcessAndRender();
	}

	void Renderer::EndScene() {

	}

	void Renderer::OnShutdown() {
		CORE_LOG_TRACE("Renderer is shutdown");
		RenderCommand::OnShutdown();
	}
}
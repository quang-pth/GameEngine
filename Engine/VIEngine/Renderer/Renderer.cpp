#include"Renderer.h"
#include"Core/Logger/Logger.h"
#include"RenderCommand.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(Renderer)

	RenderCommandQueue Renderer::sRenderCommandQueue;

	void Renderer::Submit(const RenderCallback& renderCallback) {
		if (Application::Get().GetPerFrameData().IsCatchUpPhase) return;

		sRenderCommandQueue.Enqueue(renderCallback);
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
		CORE_LOG_TRACE("Renderer init success");
		Submit([rendererSpec = appConfig.RendererSpec]() {
			RenderCommand::OnInit(rendererSpec);
		});
	}

	bool Renderer::BeginScene() {
		return true;
	}

	void Renderer::Render() {
		sRenderCommandQueue.ProcessAndRender();
	}

	void Renderer::EndScene() {

	}

	void Renderer::OnShutDown() {
		CORE_LOG_TRACE("Renderer is shutdown");
		Submit([]() {
			RenderCommand::OnShutdown();
		});
	}
}
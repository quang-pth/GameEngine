#include"Renderer.h"
#include"Core/Logger/Logger.h"
#include"RenderCommand.h"

namespace VIEngine {
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

	void Renderer::DrawIndexed(uint32_t count, ERendererPrimitive primitive, uint32_t offset) {
		Submit([primitive, count, offset]() {
			RenderCommand::DrawIndexed(count, primitive, offset);
		});
	}

	void Renderer::OnInit(const ApplicationConfiguration& appConfig) {
		Submit([rendererSpec = appConfig.RendererSpec]() {
			CORE_LOG_TRACE("Renderer init success");
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
		Submit([]() {
			CORE_LOG_TRACE("Renderer is shutdown");
			RenderCommand::OnShutdown();
		});
	}
}
#include"Renderer.h"
#include"Core/Logger/Logger.h"
#include"Core/Application.h"
#include"RenderCommand.h"

namespace VIEngine {
	RenderCommandQueue Renderer::sRenderCommandQueue;
	std::vector<BatchRenderer*> Renderer::sBatchRenderers;
	MemoryManager Renderer::sMemoryManager;

	void Renderer::Submit(const RenderCallback& renderCallback) {
		if (Application::Get().GetPerFrameData().IsCatchUpPhase) return;

		sRenderCommandQueue.Enqueue(renderCallback);
	}

	void Renderer::ClearColor(float r, float g, float b, float w) {
		Submit([r, g, b, w]() {
			RenderCommand::ClearColor(r, g, b, w);
		});
	}

	void Renderer::DrawIndexed(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) {
		Submit([nums, primitive, offset]() {
			RenderCommand::DrawIndexed(nums, primitive, offset);
		});
	}

	void Renderer::SetAlphaState(bool enable, ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) {
		Submit([enable, source, destination, blendEquation]() {
			RenderCommand::SetAlphaState(enable, source, destination, blendEquation);
		});
	}

	void Renderer::ActivateTexture(uint8_t index) {
		Submit([index]() {
			RenderCommand::ActivateTexture(index);
		});
	}

	void Renderer::BindTexture2D(uint8_t textureID) {
		Submit([textureID]() {
			RenderCommand::BindTexture2D(textureID);
		});
	}

	void Renderer::OnInit(const ApplicationConfiguration& appConfig) {
		sBatchRenderers.push_back(sMemoryManager.NewPerFrame<BatchRenderer>());
		Submit([rendererSpec = appConfig.RendererSpec]() {
			RenderCommand::OnInit(rendererSpec);
			CORE_LOG_INFO("Renderer init success");
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
			RenderCommand::OnShutdown();
			for (auto iter = sBatchRenderers.begin(); iter != sBatchRenderers.end(); ++iter) {
				sBatchRenderers.erase(iter);
			}
			sBatchRenderers.clear();
			CORE_LOG_INFO("Renderer is shutdown");
		});
	}

	void Renderer::StartSpriteBatch() {
		// TODO: Fix memory leaks here later
		// sBatchRenderers.push_back(sMemoryManager.NewPerFrame<BatchRenderer>());
		sBatchRenderers.back()->Begin();
	}

	void Renderer::SubmitSpriteBatch(const SpriteBatch& spriteBatch) {
		if (Application::Get().GetPerFrameData().IsCatchUpPhase) return;
		sBatchRenderers.back()->InsertBatch(spriteBatch);
	}

	void Renderer::EndSpriteBatch() {
		sBatchRenderers.back()->End();
		// sBatchRenderers.clear();
	}
}
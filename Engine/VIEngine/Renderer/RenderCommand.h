#pragma once

#include"pch.h"
#include"RendererAPI.h"
#include"Core/Type/RTTI.h"

namespace VIEngine {
	struct VI_API RenderData {
		bool IsEnable = false;
		ERendererState EnableRendererState = ERendererState::None;
		ERendererBlendEquation BlendEquation = ERendererBlendEquation::Add;
		ERendererBlendFunction BlendSource = ERendererBlendFunction::None;
		ERendererBlendFunction BlendDestination = ERendererBlendFunction::None;

		ERendererState DisableRendererState = ERendererState::None;
	};

	class VI_API RenderCommand {
	public:
		static void ClearColor(float r, float g, float b, float w) { sInstance->ClearColorImpl(r, g, b, w); }
		static void DrawIndexed(uint32_t nums, ERendererPrimitive primitive = ERendererPrimitive::Triangles, uint32_t offset = 0) { sInstance->DrawIndexedImpl(nums, primitive, offset); }
		static void SetAlphaState(bool enable, ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) { sInstance->SetAlphaStateImpl(enable, source, destination, blendEquation); }
		static void ActivateTexture(uint8_t index) { return sInstance->ActivateTextureImpl(index); }
		static void BindTexture2D(uint8_t textureID) { return sInstance->BindTexture2DImpl(textureID); }

	protected:
		virtual void ClearColorImpl(float r, float g, float b, float w) = 0;
		virtual void DrawIndexedImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) = 0;
		virtual void SetAlphaStateImpl(bool enable, ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) = 0;
		virtual void ActivateTextureImpl(uint8_t index) = 0;
		virtual void BindTexture2DImpl(uint8_t textureID) = 0;

	public:
		static void OnInit(ERendererSpec rendererSpec);
		static void OnShutdown();
	public:
		virtual ~RenderCommand() = default;
	protected:
		RenderCommand() = default;

	protected:
		static RenderCommand* sInstance;
	};

	class OpenGLRenderCommand : public RenderCommand {
	public:
		DECLARE_RTTI
	public:
		OpenGLRenderCommand();
		~OpenGLRenderCommand();
	protected:
		virtual void ClearColorImpl(float r, float g, float b, float w = 1.0f) override;
		virtual void DrawIndexedImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) override;
		virtual void SetAlphaStateImpl(bool enable, ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) override;
		virtual void ActivateTextureImpl(uint8_t index) override;
		virtual void BindTexture2DImpl(uint8_t textureID) override;
	private:
		RenderData mRenderData;
	};
}
#pragma once

#include"pch.h"
#include"RendererAPI.h"
#include"Core/Type/RTTI.h"

namespace VIEngine {
	struct VI_API RenderData {
		ERendererState EnableRendererState = ERendererState::None;
		ERendererBlendEquation BlendEquation = ERendererBlendEquation::Add;
		ERendererBlendFunction BlendSource = ERendererBlendFunction::None;
		ERendererBlendFunction BlendDestination = ERendererBlendFunction::None;

		ERendererState DisableRendererState = ERendererState::None;
	};

	class VI_API RenderCommand {
	public:
		static void ClearColor(float r, float g, float b, float w) { sInstance->ClearColorImpl(r, g, b, w); }
		static void DrawIndexed(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) { sInstance->DrawIndexedImpl(nums, primitive, offset); }
		static void EnableBlending(ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) { sInstance->EnableBlendingImpl(source, destination, blendEquation); }
		static void DisableBlending() { sInstance->DisableBlendingImpl(); }

	protected:
		virtual void ClearColorImpl(float r, float g, float b, float w) = 0;
		virtual void DrawIndexedImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) = 0;
		virtual void EnableBlendingImpl(ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) = 0;
		virtual void DisableBlendingImpl() = 0;

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
		virtual void EnableBlendingImpl(ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) override;
		virtual void DisableBlendingImpl() override;
	private:
		RenderData mRenderData;
	};
}
#pragma once

#include"pch.h"
#include"RendererAPI.h"
#include"Core/Type/RTTI.h"

namespace VIEngine {
	class VI_API RenderCommand {
	public:
		VI_FORCE_INLINE static void ClearColor(float r, float g, float b, float w = 1.0f) { sInstance->ClearColorImpl(r, g, b, w); }
		static void OnInit(ERendererSpec rendererSpec);
		static void OnShutdown();
	protected:
		static RenderCommand* sInstance;

	public:
		virtual ~RenderCommand() = default;
	protected:
		virtual void ClearColorImpl(float r, float g, float b, float w = 1.0f) = 0;
	protected:
		RenderCommand() = default;
	};

	class VI_API OpenGLRenderCommand : public RenderCommand {
	public:
		DECLARE_RTTI

	public:
		OpenGLRenderCommand();
		~OpenGLRenderCommand();
		virtual void ClearColorImpl(float r, float g, float b, float w = 1.0f) override;
	};
}
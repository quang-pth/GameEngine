#pragma once

#include"pch.h"
#include"RendererAPI.h"
#include"Core/Type/RTTI.h"

namespace VIEngine {
	class VI_API RenderCommand {
	public:
		static void ClearColor(float r, float g, float b, float w = 1.0f) { sInstance->ClearColorImpl(r, g, b, w); }

	protected:
		virtual void ClearColorImpl(float r, float g, float b, float w = 1.0f) = 0;

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
	protected:
		virtual void ClearColorImpl(float r, float g, float b, float w = 1.0f) override;
	};
}
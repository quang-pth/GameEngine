#pragma once

#include"pch.h"
#include"RendererAPI.h"
#include"Core/Type/RTTI.h"

namespace VIEngine {
	class VI_API RenderCommand {
	public:
		static void ClearColor(float r, float g, float b, float w = 1.0f) { sInstance->ClearColorImpl(r, g, b, w); }
		static void DrawIndexed(uint32_t count, ERendererPrimitive renderMode = ERendererPrimitive::Triangles, uint32_t offset = 0) { sInstance->DrawIndexedImpl(count, renderMode, offset); }

	protected:
		virtual void ClearColorImpl(float r, float g, float b, float w = 1.0f) = 0;
		virtual void DrawIndexedImpl(uint32_t count, ERendererPrimitive renderMode = ERendererPrimitive::Triangles, uint32_t offset = 0) = 0;

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
	protected:
		virtual void ClearColorImpl(float r, float g, float b, float w = 1.0f) override;
		virtual void DrawIndexedImpl(uint32_t count, ERendererPrimitive renderMode = ERendererPrimitive::Triangles, uint32_t offset = 0) override;
	private:
		uint32_t mVertexArrayID;
	};
}
#pragma once

#include"pch.h"
#include"Core/Application.h"
#include"RenderCommandQueue.h"

namespace VIEngine {
	class VI_API Renderer {
	public:
		static void Submit(const RenderCallback&);
		static void ClearColor(float r, float g, float b, float w = 1.0f);
		static void DrawIndexed(uint32_t count, ERendererPrimitive primitive = ERendererPrimitive::Triangles, uint32_t offset = 0);
	private:
		static RenderCommandQueue sRenderCommandQueue;
	public:
		~Renderer() = default;
		static void OnInit(const ApplicationConfiguration&);
		static bool BeginScene();
		static void Render();
		static void EndScene();
		static void OnShutDown();
	protected:
		Renderer() = default;
	};
}
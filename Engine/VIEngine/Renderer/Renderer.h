#pragma once

#include"pch.h"
#include"Core/Type/RTTI.h"
#include"Core/Application.h"
#include"RenderCommandQueue.h"

namespace VIEngine {
	class VI_API Renderer {
	public:
		DECLARE_RTTI
	public:
		static void Submit(const RenderCallback&);
		static void ClearColor(float r, float g, float b, float w = 1.0f);
	private:
		static RenderCommandQueue sRenderCommandQueue;
	public:
		Renderer();
		~Renderer();

		void OnInit(const ApplicationConfiguration&);
		bool BeginScene();
		void Render();
		void EndScene();
		void OnShutDown();
	};
}
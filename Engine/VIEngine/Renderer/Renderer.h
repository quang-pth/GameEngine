#pragma once

#include"pch.h"
#include"Core/Application.h"

namespace VIEngine {
	class VI_API Renderer {
	public:
		Renderer();
		~Renderer();

		bool Init(const ApplicationConfiguration& config);
		bool BeginScene();
		void Render();
		void EndScene();
		void Shutdown();
	};
}
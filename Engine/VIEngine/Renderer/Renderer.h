#pragma once

#include"pch.h"
#include"Core/Type/RTTI.h"

namespace VIEngine {
	class VI_API Renderer {
	public:
		DECLARE_RTTI

	public:
		Renderer();
		~Renderer();

		void OnInit();
		bool BeginScene();
		void Render();
		void EndScene();
		void ShutDown();
	};
}
#pragma once

#include"pch.h"

namespace VIEngine {
	struct VI_API ApplicationConfiguration {
		int Width, Height;
		const char* Title;
	};

	class VI_API Application {
	public:
		virtual ~Application() = default;
		bool Init();
		virtual void OnInitClient() = 0;
		void Run();
		virtual void OnShutdownClient() = 0;
		void Shutdown();
	protected:
		Application() = default;
		Application(const ApplicationConfiguration&);
	private:
		ApplicationConfiguration mConfig;
	};

	extern Application* CreateApplication();
}
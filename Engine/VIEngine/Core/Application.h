#pragma once

#include"pch.h"
#include"Window/WindowPlatform.h"
#include"Core/Event/EventDispatcher.h"

namespace VIEngine {
	struct VI_API ApplicationConfiguration {
		int Width, Height;
		const char* Title;
		EWindowPlatformSpec WindowSpec;
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
		bool OnWindowResizedEvent(const WindowResizedEvent&);
	private:
		ApplicationConfiguration mConfig;
		Unique<NativeWindow> mNativeWindow;
		EventDispatcher mEventDispatcher;
	};

	extern Application* CreateApplication();
}
#include"Application.h"
#include<iostream>

#include"Core/Logger/Logger.h"

namespace VIEngine {
	Application::Application(const ApplicationConfiguration& config) : mConfig(config), mEventDispatcher() {
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec));
    }

	bool Application::Init() {
		Logger::Init();

		if (!mNativeWindow->Init(mConfig, &mEventDispatcher)) {
			return false;
		}

		mEventDispatcher.AddEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(OnWindowResizedEvent));

		return true;
	}

	void Application::Run() {
		CORE_LOG_INFO("App is running: ({0}, {1}, {2})", mConfig.Width, mConfig.Height, mConfig.Title);

		OnInitClient();

		while (!mNativeWindow->ShouldClose()) {
			mNativeWindow->Swapbuffers();

			mNativeWindow->PollsEvent();
		}

		OnShutdownClient();
	}

	void Application::Shutdown() {
		mNativeWindow->Shutdown();
	}

	bool Application::OnWindowResizedEvent(const WindowResizedEvent& eventContext) {
		CORE_LOG_TRACE("(Width: {0}, Height: {1})", eventContext.GetWidth(), eventContext.GetHeight());
		return false;
	}
}
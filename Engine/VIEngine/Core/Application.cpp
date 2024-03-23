#include"Application.h"
#include<iostream>

#include"Core/Logger/Logger.h"
#include"Core/Event/IEvent.h"
#include"Core/Event/EventDispatcher.h"

namespace VIEngine {
	Application::Application(const ApplicationConfiguration& config) : mConfig(config) {
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec));
    }

	bool Application::Init() {
		Logger::Init();

		if (!mNativeWindow->Init(mConfig)) {
			return false;
		}

		EventDispatcher::AddEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(OnWindowResizedEvent));

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

	bool Application::OnWindowResizedEvent(const WindowResizedEvent& windowResizedEvent) {
		// TODO: Resize framebuffers
		CORE_LOG_TRACE("(Width: {0}, Height: {1})", windowResizedEvent.GetWidth(), windowResizedEvent.GetHeight());
		return true;
	}
}
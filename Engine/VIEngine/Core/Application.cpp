#include"Application.h"
#include<iostream>

#include"Core/Logger/Logger.h"

namespace VIEngine {
	Application::Application(const ApplicationConfiguration& config) : mConfig(config) {
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec));
    }

	bool Application::Init() {
		Logger::Init();

		if (!mNativeWindow->Init(mConfig)) {
			return false;
		}

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
}
#include"Application.h"
#include<iostream>

#include"Core/Logger/Logger.h"
#include"Window/Window.h"

namespace VIEngine {
	Application::Application(const ApplicationConfiguration& config) : mConfig(config) {
    }

	bool Application::Init() {
		Logger::Init();
	}

	void Application::Run() {
		CORE_LOG_INFO("App is running: ({0}, {1}, {2})", mConfig.Width, mConfig.Height, mConfig.Title);

		OnInitClient();

		// Loop

		OnShutdownClient();
	}

	void Application::Shutdown() {

	}
}
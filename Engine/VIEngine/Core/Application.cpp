#include"Application.h"
#include<iostream>

#include"Core/Logger/Logger.h"

namespace VIEngine {
	Application::Application(const ApplicationConfiguration& config) : mConfig(config) {
		Logger::Init();
    }

	void Application::Run() {
		CORE_LOG_INFO("App is running: ({0}, {1}, {2})", mConfig.Width, mConfig.Height, mConfig.Title);
	}
}
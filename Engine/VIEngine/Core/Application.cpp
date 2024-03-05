#include"Application.h"
#include<iostream>

#include"Core/Window/Window.h"
#include"Core/Logger/Logger.h"

namespace VIEngine {
	Application::Application(const ApplicationConfiguration& config) : mConfig(config) {
    }

	bool Application::Init() {
		Logger::Init();
		
		if (!NativeWindow::Init(mConfig)) {
			return false;
		}

		CORE_LOG_INFO("App init successfully");

		return true;
	}

	void Application::Run() {
		OnInitClient();
		while (!NativeWindow::ShouldClosed()) {
			NativeWindow::SwapBuffers();

			NativeWindow::PollsEvent();
		}
		OnShutdownClient();
	}

	void Application::Shutdown() {
		NativeWindow::Shutdown();
	}
}
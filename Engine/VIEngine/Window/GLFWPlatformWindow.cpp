#include"Window.h"

#include"pch.h"

#include"Core/Application.h"
#include"Core/Logger/Logger.h"

#define GLAD_GL_IMPLEMENTATION
#include<glad/gl.h>
#include<GLFW/glfw3.h>

namespace VIEngine {
	GLFWPlatformWindow::GLFWPlatformWindow() : mWindow(nullptr) {

	}

	GLFWPlatformWindow::~GLFWPlatformWindow() {
		
	}

	bool GLFWPlatformWindow::Init(const ApplicationConfiguration& config) {
		if (!glfwInit()) {
			CORE_LOG_CRITICAL("GLFW init failed");
			return false;
		}

		// Setup context for Opengl 4.3 Core
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		mWindow = glfwCreateWindow(config.Width, config.Height, config.Title, nullptr, nullptr);
		if (!mWindow) {
			CORE_LOG_CRITICAL("Window created failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Window created success");

		glfwMakeContextCurrent(mWindow);

		if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
			CORE_LOG_CRITICAL("Glad loaded failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Glad loaded success");

		return true;
	}

	void GLFWPlatformWindow::Shutdown() {
		glfwTerminate();
	}

	void GLFWPlatformWindow::Swapbuffers() {
		glClearColor(1.0f, 0.3f, .8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mWindow);
	}

	void GLFWPlatformWindow::PollsEvent() {
		glfwPollEvents();
	}

	bool GLFWPlatformWindow::ShouldClose() {
		return glfwWindowShouldClose(mWindow);
	}
}
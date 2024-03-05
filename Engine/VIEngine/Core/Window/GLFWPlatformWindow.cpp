#include"Window.h"

#define GLAD_GL_IMPLEMENTATION
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include"Core/Logger/Logger.h"
#include<Core/Application.h>

namespace VIEngine {
	bool GLFWPlatformWindow::InitImpl(const struct ApplicationConfiguration& appConfig) {
		if (!glfwInit()) {
			CORE_LOG_CRITICAL("Failed to init GLFW Window");
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		mWindow = glfwCreateWindow(appConfig.Width, appConfig.Height, appConfig.Title, NULL, NULL);
		if (!mWindow) {
			CORE_LOG_CRITICAL("Failed to create GLFW window");
			glfwTerminate();
			return false;
		}
		CORE_LOG_TRACE("GLFW Window init with (Width: {0}, Height: {1}, Title: {2})", appConfig.Width, appConfig.Height, appConfig.Title);

		glfwMakeContextCurrent(mWindow);

		if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
			CORE_LOG_CRITICAL("Failed to init Glad");
			return false;
		}
		CORE_LOG_TRACE("Glad init successfully");

		return true;
	}

	void GLFWPlatformWindow::PollsEventImpl()
	{
		glfwPollEvents();
	}

	bool GLFWPlatformWindow::ShouldClosedImpl()
	{
		return glfwWindowShouldClose(mWindow);
	}

	void GLFWPlatformWindow::SwapBuffersImpl()
	{
		glClearColor(0.3f, 0.2f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mWindow);
	}	
	
	void GLFWPlatformWindow::ShutdownImpl()
	{
		glfwTerminate();
	}
}
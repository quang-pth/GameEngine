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
		VI_FREE_MEMORY(mData.Input.Keyboard);
		VI_FREE_MEMORY(mData.Input.Mouse);
	}

	bool GLFWPlatformWindow::Init(const ApplicationConfiguration& config, EventDispatcher* eventDispatcher) {
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

		mData.Dispatcher = eventDispatcher;
		mData.Input.Keyboard = WindowPlatform::CreateKeyboard(config.WindowSpec, mWindow);
		mData.Input.Mouse = WindowPlatform::CreateMouse(config.WindowSpec, mWindow);

		glfwSetWindowUserPointer(mWindow, &mData);

		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);

			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Width = width;
			data->Height = height;
			WindowResizedEvent eventContext(width, height);
			data->Dispatcher->DispatchEventListener<WindowResizedEvent>(eventContext);
		});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int keyCode, int scanCode, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS) {
				data->Dispatcher->DispatchEventListener<KeyPressedEvent>({ keyCode });
			}
			else if (action == GLFW_REPEAT) {
				data->Dispatcher->DispatchEventListener<KeyHeldEvent>({ keyCode });
			}
			else if (action == GLFW_RELEASE) {
				data->Dispatcher->DispatchEventListener<KeyReleasedEvent>({ keyCode });
			}
		});

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS) {
				data->Dispatcher->DispatchEventListener<MouseButtonPressedEvent>({ button });
			}
			else if (action == GLFW_RELEASE) {
				data->Dispatcher->DispatchEventListener<MouseButtonReleasedEvent>({ button });
			}
		});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double positionX, double positionY) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			static double lastFrameX = positionX;
			static double lastFrameY = positionY;

			double offsetX = positionX - lastFrameX;
			double offsetY = positionY - lastFrameY;

			data->Dispatcher->DispatchEventListener<MouseMovedEvent>({ positionX, positionY, offsetX, offsetY });
			data->Input.Mouse->SetPosition(positionX, positionY);
			data->Input.Mouse->SetOffset(offsetX, offsetY);

			lastFrameX = positionX;
			lastFrameY = positionY;
		});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double scrollX, double scrollY) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Dispatcher->DispatchEventListener<MouseScrolledEvent>({ scrollX, scrollY });
			data->Input.Mouse->SetScroll(scrollX, scrollY);
		});

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

	InputState* GLFWPlatformWindow::GetInputState() {
		return &mData.Input;
	}

	double GLFWPlatformWindow::GetTimeSeconds() const {
		return glfwGetTime();
	}
}
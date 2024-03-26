#include"Window.h"

#include"pch.h"

#include"Core/Application.h"
#include"Core/Logger/Logger.h"
#include"Core/Event/EventDispatcher.h"
#include"Core/Input/InputState.h"
#include"Window/WindowPlatform.h"

#define GLAD_GL_IMPLEMENTATION
#include<glad/gl.h>
#include<GLFW/glfw3.h>

namespace VIEngine {
	GLFWPlatformWindow::GLFWPlatformWindow() : mWindow(nullptr) {

	}

	GLFWPlatformWindow::~GLFWPlatformWindow() {
		
	}

	bool GLFWPlatformWindow::Init(const ApplicationConfiguration& config, EventDispatcher* eventDispatcher) {
		VI_ASSERT(config.WindowSpec == EWindowPlatformSpec::GLFW && "Invalid window spec for GLFW");

		if (!glfwInit()) {
			CORE_LOG_CRITICAL("GLFW init failed");
			return false;
		}

		// Setup context for Opengl 4.3 Core
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		mWindow = glfwCreateWindow(config.Width, config.Height, config.Title, nullptr, nullptr);
		if (!mWindow) {
			CORE_LOG_CRITICAL("Window created failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Window created success");
		
		mData.Width = config.Width;
		mData.Height = config.Height;
		mData.Dispatcher = eventDispatcher;
		mData.Input.Keyboard = WindowPlatform::CreateInput(config.WindowSpec, mWindow);
		mData.Input.Mouse = WindowPlatform::CreateMouse(config.WindowSpec, mWindow);

		glfwSetWindowUserPointer(mWindow, &mData);

		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
			WindowResizedEvent windowResizedEvent(width, height);

			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
			data->Width = width;
			data->Height = height;

			data->Dispatcher->DispatchEventListener<WindowResizedEvent>(windowResizedEvent);
		});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS) {
				data->Dispatcher->DispatchEventListener<KeyPressedEvent>({ key });
			}
			else if (action == GLFW_RELEASE) {
				data->Dispatcher->DispatchEventListener<KeyReleasedEvent>({ key });
			}
			else if (action == GLFW_REPEAT) {
				data->Dispatcher->DispatchEventListener<KeyHeldEvent>({ key });
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

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Input.Mouse->SetScroll(xOffset, yOffset);
			data->Dispatcher->DispatchEventListener<MouseScrolledEvent>({ xOffset, yOffset });
		});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double x, double y) {
			static double prevX = x;
			static double prevY = y;

			double xOffset = x - prevX;
			double yOffset = y - prevY;

			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Input.Mouse->SetPosition(x, y);
			data->Input.Mouse->SetOffset(xOffset, yOffset);

			prevX = x;
			prevY = y;
		});

		glfwMakeContextCurrent(mWindow);

		mData.Dispatcher = eventDispatcher;

		glfwSetWindowUserPointer(mWindow, &mData);

		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);

			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Width = width;
			data->Height = height;
			WindowResizedEvent eventContext(width, height);
			data->Dispatcher->DispatchEventListener<WindowResizedEvent>(eventContext);
		});

		if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
			CORE_LOG_CRITICAL("Glad loaded failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Glad loaded success");;

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

	InputState* GLFWPlatformWindow::GetInputState() const {
		return (InputState*)&(mData.Input);
	}
}
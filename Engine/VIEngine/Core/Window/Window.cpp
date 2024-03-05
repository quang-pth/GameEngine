#include"Window.h"

namespace VIEngine {
	WindowPlatformType NativeWindow::PlatformType = WindowPlatformType::GLFW;
	NativeWindow* NativeWindow::Instance = NativeWindow::Create();

	NativeWindow* NativeWindow::Create() {
		NativeWindow* window = nullptr;
		switch (NativeWindow::PlatformType)
		{
			case VIEngine::WindowPlatformType::GLFW: window = new GLFWPlatformWindow();
			case VIEngine::WindowPlatformType::SDL: VI_ASSERT("SDL window not supported");
			case VIEngine::WindowPlatformType::None: VI_ASSERT("Unknown Window return type");
		}
		return dynamic_cast<NativeWindow*>(window);
	}
}
#pragma once

#include"Window.h"


namespace VIEngine {
	class WindowPlatform {
	public:
		static NativeWindow* Create(EWindowPlatformSpec spec);
		static class KeyboardInput* CreateKeyboard(EWindowPlatformSpec spec, void* window);
		static class MouseInput* CreateMouse(EWindowPlatformSpec spec, void* window);
	private:
		WindowPlatform() = default;
		~WindowPlatform() = default;
		WindowPlatform(WindowPlatform&) = default;
	};
}
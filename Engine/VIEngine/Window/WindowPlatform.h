#pragma once

#include"Window.h"

namespace VIEngine {
	class KeyboardInput;
	class MouseInput;

	class WindowPlatform {
	public:
		static NativeWindow* Create(EWindowPlatformSpec spec);
		static KeyboardInput* CreateInput(EWindowPlatformSpec spec, void* window);
		static MouseInput* CreateMouse(EWindowPlatformSpec spec, void* window);
	private:
		WindowPlatform() = default;
		~WindowPlatform() = default;
		WindowPlatform(WindowPlatform&) = default;
	};
}
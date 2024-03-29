#include"WindowPlatform.h"

#include"pch.h"
#include"Core/Input/InputState.h"

namespace VIEngine {
	NativeWindow* WindowPlatform::Create(EWindowPlatformSpec spec) {
		NativeWindow* window = nullptr;

		switch (spec)
		{
			case EWindowPlatformSpec::GLFW: window = new GLFWPlatformWindow(); break;
			case EWindowPlatformSpec::SDL: VI_ASSERT("SDL Window not supported"); break;
			case EWindowPlatformSpec::None: default: VI_ASSERT("Unknown Window detected");
		}

		return window;
	}

	KeyboardInput* WindowPlatform::CreateKeyboard(EWindowPlatformSpec spec, void* window) {
		KeyboardInput* input = nullptr;

		switch (spec)
		{
			case EWindowPlatformSpec::GLFW: input = new GLFWKeyboardInput(window); break;
			case EWindowPlatformSpec::SDL: VI_ASSERT("SDL Keyboard Input not supported"); break;
			case EWindowPlatformSpec::None: default: VI_ASSERT("Unknown Keyboard Input detected");
		}

		return input;
	}

	MouseInput* WindowPlatform::CreateMouse(EWindowPlatformSpec spec, void* window) {
		MouseInput* input = nullptr;

		switch (spec)
		{
			case EWindowPlatformSpec::GLFW: input = new GLFWMouseInput(window); break;
			case EWindowPlatformSpec::SDL: VI_ASSERT("SDL Mouse Input not supported"); break;
			case EWindowPlatformSpec::None: default: VI_ASSERT("Unknown Mouse Input detected");
		}

		return input;
	}
}
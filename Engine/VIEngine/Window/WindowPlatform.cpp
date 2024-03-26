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
			case EWindowPlatformSpec::None:
			default: VI_ASSERT("Unknown Window detected"); break;
		}

		return window;
	}
	
	KeyboardInput* WindowPlatform::CreateInput(EWindowPlatformSpec spec, void* window) {
		KeyboardInput* keyboardInput = nullptr;

		switch (spec)
		{
			case EWindowPlatformSpec::GLFW: keyboardInput = new GLFWKeyboardInput(window); break;
			case EWindowPlatformSpec::SDL: VI_ASSERT("SDL Keyboard not supported"); break;
			case EWindowPlatformSpec::None:
			default: VI_ASSERT("Unknown Keyboard detected"); break;
		}

		return keyboardInput;
	}	

	MouseInput* WindowPlatform::CreateMouse(EWindowPlatformSpec spec, void* window) {
		MouseInput* mouseInput = nullptr;

		switch (spec)
		{
			case EWindowPlatformSpec::GLFW: mouseInput = new GLFWMouseInput(window); break;
			case EWindowPlatformSpec::SDL: VI_ASSERT("SDL Mouse not supported"); break;
			case EWindowPlatformSpec::None:
			default: VI_ASSERT("Unknown Mouse detected"); break;
		}

		return mouseInput;
	}
}
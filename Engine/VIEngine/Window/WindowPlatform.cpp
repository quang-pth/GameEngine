#include"WindowPlatform.h"

#include"pch.h"

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

		return dynamic_cast<NativeWindow*>(window);
	}
}
#include"WindowPlatform.h"

#include"pch.h"

namespace VIEngine {
	NativeWindow* WindowPlatform::Create(EWindowPlatformSpec spec) {
		NativeWindow* window = nullptr;

		switch (spec)
		{
			case EWindowPlatformSpec::GLFW: window = new GLFWPlatformWindow();
			case EWindowPlatformSpec::SDL: VI_ASSERT("SDL Window not supported");
			case EWindowPlatformSpec::None: VI_ASSERT("Unknown Window detected");
			default: VI_ASSERT("Unknown Window detected");
		}

		return dynamic_cast<NativeWindow*>(window);
	}
}
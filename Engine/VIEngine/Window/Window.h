#pragma once

class GLFWwindow;

#include"Core/Input/InputState.h"

namespace VIEngine {
	enum class EWindowPlatformSpec {
		GLFW,
		SDL,
		None
	};

	class EventDispatcher;
	struct ApplicationConfiguration;
	
	struct WindowData {
		int32_t Width, Height;
		EventDispatcher* Dispatcher;
		InputState Input;
	};

	class NativeWindow {
	public:
		virtual ~NativeWindow() = default;
		virtual bool Init(const ApplicationConfiguration&, EventDispatcher*) = 0;
		virtual void Shutdown() = 0;
		virtual void Swapbuffers() = 0;
		virtual void PollsEvent() = 0;
		virtual bool ShouldClose() = 0;
		virtual InputState* GetInputState() = 0;
		virtual float GetTimeSeconds() = 0;
	protected:
		NativeWindow() = default;
		NativeWindow(NativeWindow&) = default;
	};

	class GLFWPlatformWindow : public NativeWindow {
	public:
		GLFWPlatformWindow();
		~GLFWPlatformWindow();
		virtual bool Init(const ApplicationConfiguration&, EventDispatcher*) override;
		virtual void Shutdown() override;
		virtual void Swapbuffers() override;
		virtual void PollsEvent() override;
		virtual bool ShouldClose() override;
		virtual InputState* GetInputState() override;
		virtual float GetTimeSeconds() override;
	private:
		GLFWwindow* mWindow;
		WindowData mData;
	};
}
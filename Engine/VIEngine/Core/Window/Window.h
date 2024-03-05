#pragma once

#include"pch.h"

class GLFWwindow;

namespace VIEngine {
	enum class WindowPlatformType {
		GLFW,
		SDL,
		None
	};

	class NativeWindow {
	public:
		static NativeWindow* Instance;
	public:
		static NativeWindow* Create();
		static bool Init(const struct ApplicationConfiguration& appConfig) { return Instance->InitImpl(appConfig); }
		static void PollsEvent() { Instance->PollsEventImpl(); }
		static bool ShouldClosed() { return Instance->ShouldClosedImpl(); }
		static void SwapBuffers() { Instance->SwapBuffersImpl(); }
		static void Shutdown() { Instance->ShutdownImpl(); }
	protected:
		NativeWindow() = default;
		virtual ~NativeWindow() = default;
		
		virtual bool InitImpl(const struct ApplicationConfiguration& appConfig) = 0;
		virtual void PollsEventImpl() = 0;
		virtual bool ShouldClosedImpl() = 0;
		virtual void SwapBuffersImpl() = 0;
		virtual void ShutdownImpl() = 0;
	private:
		static WindowPlatformType PlatformType;
	private:
		NativeWindow(NativeWindow&) = default;
	};

	class GLFWPlatformWindow : public NativeWindow {
	public:
		GLFWPlatformWindow() = default;
		GLFWPlatformWindow(GLFWPlatformWindow&) = default;
		virtual bool InitImpl(const struct ApplicationConfiguration& appConfig) override;
		virtual void PollsEventImpl() override;
		virtual bool ShouldClosedImpl() override;
		virtual void SwapBuffersImpl() override;
		virtual void ShutdownImpl() override;
	protected:
		~GLFWPlatformWindow() = default;
	private:
		GLFWwindow* mWindow;
	};
}
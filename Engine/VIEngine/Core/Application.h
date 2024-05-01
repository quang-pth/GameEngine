#pragma once

#include"pch.h"
#include"Window/WindowPlatform.h"
#include"Core/Event/EventDispatcher.h"
#include"Core/Layer/LayerStack.h"
#include"JobSystem/ThreadPool.h"
#include"GameObject/GameObject.h"
#include"ECS/Coordinator.h"

namespace VIEngine {
	struct VI_API ApplicationConfiguration {
		int Width, Height;
		const char* Title;
		EWindowPlatformSpec WindowSpec;
	};

	class VI_API Application {
	public:
		static Application& GetInstance();
	private:
		static Application* sInstance;
	public:
		virtual ~Application() = default;
		bool Init();
		virtual void OnInitClient() = 0;
		void Run();
		virtual void OnShutdownClient() = 0;
		void Shutdown();
		GameObject CreateGameObject();
	protected:
		Application() = default;
		Application(const ApplicationConfiguration&);
		void PushLayer(Layer*);
		void PopLayer(Layer*);
		void PushOverlayLayer(Layer*);
		void PopOverlayLayer(Layer*);
	private:
		bool OnWindowResizedEvent(const WindowResizedEvent&);
		bool OnKeyPressedEvent(const KeyPressedEvent&);
		bool OnKeyHeldEvent(const KeyHeldEvent&);
		bool OnKeyReleasedEvent(const KeyReleasedEvent&);
		bool OnMouseMovedEvent(const MouseMovedEvent&);
		bool OnMouseScrolledEvent(const MouseScrolledEvent&);
		bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent&);
		bool OnMouseButtonHeldEvent(const MouseButtonHeldEvent&);
		bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent&);
	private:
		ApplicationConfiguration mConfig;
		Unique<NativeWindow> mNativeWindow;
		EventDispatcher mEventDispatcher;
		Unique<LayerStack> mLayerStack;
		Time mTime;
		class InputState* mInputState;
		Unique<ThreadPool> mThreadPool;
		Unique<ECS::Coordinator> mCoordinator;
		bool mIsRunning;
	};

	extern Application* CreateApplication();
}
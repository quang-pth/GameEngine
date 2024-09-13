#pragma once

#include"pch.h"
#include"Window/WindowPlatform.h"
#include"Core/Event/EventDispatcher.h"
#include"Core/Layer/LayerStack.h"
#include"Core/Time/Time.h"
#include"Renderer/RendererAPI.h"

namespace VIEngine {
	struct VI_API ApplicationConfiguration {
		uint16_t Width, Height;
		const char* Title;
		EWindowPlatformSpec WindowSpec;
		uint16_t MaxFPS;
		ERendererSpec RendererSpec;
	};

	struct VI_API PerFrameData {
		uint32_t FrameIndex = 0;
		bool IsCatchUpPhase = false;
	};

	namespace ECS {
		class SystemManager;
		class Coordinator;
	}

	class VI_API Application {
	public:
		static Application& Get();
	private:
		static Application* sInstance;

	public:
		virtual ~Application() = default;
		bool Init();
		virtual void OnInitClient() = 0;
		void Run();
		virtual void OnShutdownClient() = 0;
		void Shutdown();
		VI_FORCE_INLINE const PerFrameData& GetPerFrameData() const { return mPerFrameData; }
		VI_FORCE_INLINE const ApplicationConfiguration& GetConfiguration() const { return mConfig; }
	protected:
		Application() = default;
		Application(const ApplicationConfiguration&);

		void PushLayer(Layer*);
		void PushOverlayLayer(Layer*);
		void PopLayer(Layer*);
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
		LayerStack* mLayerStack;
		ECS::SystemManager* mSystemManager;
		ECS::Coordinator* mCoordinator;
		EventDispatcher mEventDispatcher;
		class InputState* mInputState;
		Time mTime;
		bool mIsRunning;
		PerFrameData mPerFrameData;
	};

	extern Application* CreateApplication();
}
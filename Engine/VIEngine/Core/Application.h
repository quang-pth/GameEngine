#pragma once

#include"pch.h"
#include"Window/WindowPlatform.h"
#include"Core/Event/EventDispatcher.h"
#include"Core/Layer/LayerStack.h"
#include"Core/Time/Time.h"
#include"Scene/Scene.h"
#include"Core/Type/Actor.h"
#include"Memory/MemoryManager.h"
#include"Input/InputState.h"
#include"Renderer/API/RendererAPI.h"

namespace VIEngine {
	struct VI_API ApplicationConfiguration {
		int Width, Height;
		const char* Title;
		EWindowPlatformSpec WindowSpec;
		uint16_t MaxFPS;
		ERendererAPI RendererAPISpec = ERendererAPI::OpenGL;
	};

	class VI_API Application {
	public:
		static MemoryManager& GetGlobalMemoryUsage();
		static Application& Get();
		static Application* sInstance;

	public:
		virtual ~Application();
		bool Init();
		virtual void OnInitClient() = 0;
		void Run();
		virtual void OnShutdownClient() = 0;
		void Shutdown();

		VI_FORCE_INLINE Shared<Scene> GetCurrentActiveScene() const { return mCurrentActiveScene; }
		VI_FORCE_INLINE class Renderer* GetRendererer() { return mRenderer; }

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
		Shared<NativeWindow> mNativeWindow;
		SCOPED_OBJECT(LayerStack, mLayerStack);
		Shared<Scene> mCurrentActiveScene;
		Shared<ECS::Coordinator> mCoordinator;
		class Renderer* mRenderer;
		class ECS::SystemManager* mSystemManager;
		EventDispatcher mEventDispatcher;
		InputState* mInputState;
		Time mTime;
		bool mIsRunning;
	};

	extern Application* CreateApplication();
}
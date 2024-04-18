#include"Application.h"
#include<iostream>

#include"Core/Logger/Logger.h"
#include"JobSystem/ThreadPool.h"

#define DISPATCH_LAYER_EVENT(eventType, eventContext) for (auto iter = mLayerStack->rbegin(); iter != mLayerStack->rend(); ++iter) {\
		Layer* layer = *iter;\
		if (!layer->IsEnabled()) return false;\
		if (layer->On##eventType(eventContext)) return false;\
	}\

namespace VIEngine {
	Application::Application(const ApplicationConfiguration& config) : mConfig(config), mEventDispatcher(), mIsRunning(true) {
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec));
		mLayerStack.reset(new LayerStack());

		size_t cpuThreads = std::thread::hardware_concurrency();
		mThreadPool.reset(new ThreadPool(cpuThreads));
    }

	bool Application::Init() {
		Logger::Init();

		if (!mNativeWindow->Init(mConfig, &mEventDispatcher)) {
			return false;
		}

		mInputState = mNativeWindow->GetInputState();

		mEventDispatcher.AddEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(OnWindowResizedEvent));
		mEventDispatcher.AddEventListener<KeyPressedEvent>(BIND_EVENT_FUNCTION(OnKeyPressedEvent));
		mEventDispatcher.AddEventListener<KeyHeldEvent>(BIND_EVENT_FUNCTION(OnKeyHeldEvent));
		mEventDispatcher.AddEventListener<KeyReleasedEvent>(BIND_EVENT_FUNCTION(OnKeyReleasedEvent));
		mEventDispatcher.AddEventListener<MouseMovedEvent>(BIND_EVENT_FUNCTION(OnMouseMovedEvent));
		mEventDispatcher.AddEventListener<MouseScrolledEvent>(BIND_EVENT_FUNCTION(OnMouseScrolledEvent));
		mEventDispatcher.AddEventListener<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(OnMouseButtonPressedEvent));
		mEventDispatcher.AddEventListener<MouseButtonHeldEvent>(BIND_EVENT_FUNCTION(OnMouseButtonHeldEvent));
		mEventDispatcher.AddEventListener<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(OnMouseButtonReleasedEvent));

		return true;
	}

	void Application::Run() {
		CORE_LOG_INFO("App is running: ({0}, {1}, {2})", mConfig.Width, mConfig.Height, mConfig.Title);

		OnInitClient();

		constexpr float MAX_DELTA_TIME = 0.05f;
		constexpr float MIN_DELTA_TIME = 1 / 60.0f; // Constraints at max 60FPS

		while (mIsRunning && !mNativeWindow->ShouldClose()) {
			static double lastFrameTime = 0.0f;

			while (mNativeWindow->GetTimeSeconds() - lastFrameTime < MIN_DELTA_TIME);

			mNativeWindow->PollsEvent();

			for (auto iter = mLayerStack->rbegin(); iter != mLayerStack->rend(); ++iter) {
				mThreadPool->SubmitJob([layer = *iter, inputState = std::move(*mInputState)]() {
					if (layer->IsEnabled()) {
						layer->OnProcessInput(inputState);
					}
				});
			}

			double currentFrameTime = mNativeWindow->GetTimeSeconds();
			double deltaTime = currentFrameTime - lastFrameTime;
			Time time(deltaTime);
			while (time > MAX_DELTA_TIME) {
				for (Layer* layer : *mLayerStack.get()) {
					mThreadPool->SubmitJob([layer = layer](const Time& time) {
						if (layer->IsEnabled()) {
							layer->OnUpdate(time);
						}
					}, MAX_DELTA_TIME);
				}
				time -= MAX_DELTA_TIME;
			}

			for (Layer* layer : *mLayerStack.get()) {
				mThreadPool->SubmitJob([layer = layer](const Time& time) {
					if (layer->IsEnabled()) {
						layer->OnUpdate(time);
					}
				}, time);
			}

			mNativeWindow->Swapbuffers();

			for (Layer* layer : *mLayerStack.get()) {
				mThreadPool->SubmitJob([layer = layer]() {
					if (layer->IsEnabled()) {
						layer->OnRender();
					}
				});
			}

			lastFrameTime = mNativeWindow->GetTimeSeconds();
		}

		OnShutdownClient();
	}

	void Application::Shutdown() {
		mThreadPool->JoinAndRelease();
		mNativeWindow->Shutdown();
	}

	void Application::PushLayer(Layer* layer) {
		mLayerStack->PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PopLayer(Layer* layer) {
		mLayerStack->PopLayer(layer);
		layer->OnDetach();
	}
	
	void Application::PushOverlayLayer(Layer* layer) {
		mLayerStack->PushOverlay(layer);
		layer->OnAttach();
	}
	
	void Application::PopOverlayLayer(Layer* layer) {
		mLayerStack->PopOverlay(layer);
		layer->OnDetach();
	}

	bool Application::OnWindowResizedEvent(const WindowResizedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(WindowResizedEvent, eventContext);
		return false;
	}

	bool Application::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
		if (eventContext.IsKey(EKeyCode::ESCAPE)) {
			mIsRunning = false;
			return true;
		}
		
		DISPATCH_LAYER_EVENT(KeyPressedEvent, eventContext);

		return false;
	}
	
	bool Application::OnKeyHeldEvent(const KeyHeldEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyHeldEvent, eventContext);

		return false;
	}
	
	bool Application::OnKeyReleasedEvent(const KeyReleasedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyReleasedEvent, eventContext);
		return false;
	}
	
	bool Application::OnMouseMovedEvent(const MouseMovedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseMovedEvent, eventContext);
		return false;
	}
	
	bool Application::OnMouseScrolledEvent(const MouseScrolledEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseScrolledEvent, eventContext);
		return false;
	}
	
	bool Application::OnMouseButtonPressedEvent(const MouseButtonPressedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonPressedEvent, eventContext);
		return false;
	}
	
	bool Application::OnMouseButtonHeldEvent(const MouseButtonHeldEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonHeldEvent, eventContext);
		return false;
	}
	
	bool Application::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonReleasedEvent, eventContext);
		return false;
	}
}
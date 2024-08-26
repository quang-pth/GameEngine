#include"Application.h"

#include"Core/Logger/Logger.h"
#include"Core/System/System.h"
#include"Memory/MemoryMonitor.h"
#include"Renderer/Renderer.h"

#define DISPATCH_LAYER_EVENT(eventType, eventContext) for (auto iter = mLayerStack->rbegin(); iter != mLayerStack->rend(); ++iter) {\
	if ((*iter)->On##eventType(eventContext)) {\
		break;\
	}\
}

namespace VIEngine {
	Application* Application::sInstance;

	MemoryManager& Application::GetGlobalMemoryUsage() {
		static MemoryManager* globalMemory = nullptr;
		if (globalMemory == nullptr) {
			globalMemory = new MemoryManager();
		}
		return *globalMemory;
	}

	Application& Application::Get() {
		VI_ASSERT(sInstance != nullptr && "Application is not initialized!");
		return *sInstance;
	}

	Application::Application(const ApplicationConfiguration& config) : mConfig(config), mEventDispatcher(), 
			mIsRunning(true), mInputState(nullptr), mTime(), mRenderer(), 
			CREATED_SCOPED_OBJECT(LayerStack, mLayerStack)
	{
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec));

		//mLayerStack.reset(GetGlobalMemoryUsage().NewOnStack<LayerStack>("LayerStack"));
		//mLayerStack.get_deleter() = VI_DELETER_ID(LayerStack);

		//mLayerStack.reset(GetGlobalMemoryUsage().NewOnStack<LayerStack>("LayerStack"));

		mCoordinator.reset(GetGlobalMemoryUsage().NewOnStack<ECS::Coordinator>("ECS Coordinator"));
		mCurrentActiveScene.reset(GetGlobalMemoryUsage().NewOnStack<Scene>("Current Active Scene", mCoordinator));
		mRenderer = GetGlobalMemoryUsage().NewOnStack<Renderer>("Renderer");
		mSystemManager = GetGlobalMemoryUsage().NewOnStack<ECS::SystemManager>("SystemManager", mCoordinator.get());

		sInstance = this;
    }

	Application::~Application() {
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

		auto& collisionSystem = mSystemManager->AddSystem<CollisionResolver>();
		auto& animationSystem = mSystemManager->AddSystem<AnimationSystem>();

		mSystemManager->AddSystemDependency(&animationSystem, &collisionSystem);

		collisionSystem.SetUpdateInterval(1.0f / (mConfig.MaxFPS * 0.5));

		mSystemManager->OnInit();

		mRenderer->OnInit(mConfig.RendererAPISpec);

		return true;
	}

	void Application::Run() {
		CORE_LOG_INFO("App is running: ({0}, {1}, {2})", mConfig.Width, mConfig.Height, mConfig.Title);

		const float MAX_DELTA_TIME = 0.05f;
		float minDeltaTime = 1.0f / mConfig.MaxFPS;

		OnInitClient();

		while (mIsRunning && !mNativeWindow->ShouldClose()) {
			static float lastFrameTime = 0.0f;

			while (mNativeWindow->GetTimeSeconds() - lastFrameTime < minDeltaTime);

			MemoryMonitor::Update();

			float currentFrameTime = mNativeWindow->GetTimeSeconds();

			mTime = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;

			mNativeWindow->PollsEvent();

			for (auto layer : *mLayerStack.get()) {
				layer->OnProcessInput(*mInputState);
			}

			mNativeWindow->Swapbuffers();

			while (mTime.GetDeltaTime() > MAX_DELTA_TIME) {
				for (auto layer : *mLayerStack.get()) {
					layer->OnUpdate(MAX_DELTA_TIME);
				}

				mSystemManager->OnUpdate(MAX_DELTA_TIME);

				mTime -= MAX_DELTA_TIME;
			}

			for (auto layer : *mLayerStack.get()) {
				layer->OnUpdate(mTime);
			}

			mSystemManager->OnUpdate(mTime);

			for (auto layer : *mLayerStack.get()) {
				layer->OnRender(mTime);
			}

			mRenderer->BeginScene();
			mRenderer->Render();
			mRenderer->EndScene();
		}

		OnShutdownClient();
	}

	void Application::Shutdown() {
		mSystemManager->OnShutdown();
		mRenderer->OnShutdown();
		mCoordinator->OnShutdown();
		mNativeWindow->Shutdown();
		
		MemoryMonitor::Clear();
		MemoryMonitor::DetecsMemoryLeaks();

		sInstance = nullptr;
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

	void Application::PushLayer(Layer* layer) {
		mLayerStack->Push(layer);
		layer->OnAttach();
	}

	void Application::PushOverlayLayer(Layer* layer) {
		mLayerStack->PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer) {
		mLayerStack->Pop(layer);
		layer->OnDetach();
	}
	
	void Application::PopOverlayLayer(Layer* layer) {
		mLayerStack->PopOverlay(layer);
		layer->OnDetach();
	}
}
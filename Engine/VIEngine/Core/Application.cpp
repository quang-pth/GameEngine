#include"Application.h"
#include<iostream>

#include"Core/Logger/Logger.h"

namespace VIEngine {
	Application::Application(const ApplicationConfiguration& config) : mConfig(config), mEventDispatcher() {
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec));
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

		while (!mNativeWindow->ShouldClose()) {
			mNativeWindow->Swapbuffers();

			//if (mInputState->Mouse->IsPressed(EMouseButton::BUTTON_LEFT)) {
			//	CORE_LOG_TRACE("Left mouse is clicked");
			//}
			//
			//if (mInputState->Mouse->IsPressed(EMouseButton::BUTTON_RIGHT)) {
			//	CORE_LOG_TRACE("Right mouse is clicked");
			//}

			//if (mInputState->Keyboard->IsPressed(EKeyCode::A)) {
			//	CORE_LOG_TRACE("A key is pressed");
			//}

			//if (mInputState->Keyboard->IsReleased(EKeyCode::A)) {
			//	CORE_LOG_TRACE("A key is released");
			//}

			mNativeWindow->PollsEvent();
		}

		OnShutdownClient();
	}

	void Application::Shutdown() {
		mNativeWindow->Shutdown();
	}

	bool Application::OnWindowResizedEvent(const WindowResizedEvent& eventContext) {
		CORE_LOG_TRACE("(Width: {0}, Height: {1})", eventContext.GetWidth(), eventContext.GetHeight());
		return false;
	}

	bool Application::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKeyCode());
		return false;
	}
	
	bool Application::OnKeyHeldEvent(const KeyHeldEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is held", (char)eventContext.GetKeyCode());
		return false;
	}
	
	bool Application::OnKeyReleasedEvent(const KeyReleasedEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is released", (char)eventContext.GetKeyCode());
		return false;
	}
	
	bool Application::OnMouseMovedEvent(const MouseMovedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse position: {0}, {1}. Mouse relative: {2}, {3}", eventContext.GetPositionX(), eventContext.GetPositionY(), eventContext.GetOffsetX(), eventContext.GetOffsetY());
		return false;
	}
	
	bool Application::OnMouseScrolledEvent(const MouseScrolledEvent& eventContext) {
		CORE_LOG_TRACE("Mouse scroll X: {0}, Mouse Scroll Y: {1}", eventContext.GetScrollX(), eventContext.GetScrollY());
		return false;
	}
	
	bool Application::OnMouseButtonPressedEvent(const MouseButtonPressedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {0} is pressed", eventContext.GetButton());
		return false;
	}
	
	bool Application::OnMouseButtonHeldEvent(const MouseButtonHeldEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {0} is held", eventContext.GetButton());
		return false;
	}
	
	bool Application::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {0} is released", eventContext.GetButton());
		return false;
	}
}
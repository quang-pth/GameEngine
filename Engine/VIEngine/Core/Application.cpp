#include"Application.h"
#include<iostream>

#include"Core/Logger/Logger.h"
#include"Core/Event/EventContext.h"
#include"Core/Event/EventDispatcher.h"
#include"Core/Input/InputState.h"

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

		// Add window event listener
		mEventDispatcher.AddEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(OnWindowResizedEvent));

		// Add input event listener
		mEventDispatcher.AddEventListener<KeyPressedEvent>(BIND_EVENT_FUNCTION(OnKeyPressedEvent));
		mEventDispatcher.AddEventListener<KeyHeldEvent>(BIND_EVENT_FUNCTION(OnKeyHeldEvent));
		mEventDispatcher.AddEventListener<KeyReleasedEvent>(BIND_EVENT_FUNCTION(OnKeyReleasedEvent));

		return true;
	}

	void Application::Run() {
		CORE_LOG_INFO("App is running: ({0}, {1}, {2})", mConfig.Width, mConfig.Height, mConfig.Title);

		OnInitClient();
		
		while (!mNativeWindow->ShouldClose()) {
			mNativeWindow->Swapbuffers();

			/*if (mInputState->Mouse->IsPressed(EMouseButton::MOUSE_BUTTON_LEFT)) {
				CORE_LOG_TRACE("Mouse left clicked");
			}
			else if (mInputState->Mouse->IsReleased(EMouseButton::MOUSE_BUTTON_LEFT)) {
				CORE_LOG_TRACE("Mouse left released");
			}*/

			//CORE_LOG_TRACE("Mouse left value: {0}", mInputState->Mouse->GetValue(EMouseButton::MOUSE_BUTTON_LEFT));
			//CORE_LOG_TRACE("L value: {0}", mInputState->Keyboard->GetValue(EKeyCode::L));

			mNativeWindow->PollsEvent();
		}

		OnShutdownClient();
	}

	void Application::Shutdown() {
		mNativeWindow->Shutdown();
	}

	bool Application::OnWindowResizedEvent(const WindowResizedEvent& eventContext) {
		// TODO: Resize framebuffers
		CORE_LOG_TRACE("(Width: {0}, Height: {1})", eventContext.GetWidth(), eventContext.GetHeight());
		return false;
	}

	bool Application::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is pressed!", (char)eventContext.GetKey());
		return false;
	}
	
	bool Application::OnKeyHeldEvent(const KeyHeldEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is held!", (char)eventContext.GetKey());
		return false;
	}

	bool Application::OnKeyReleasedEvent(const KeyReleasedEvent& eventContext) {
		CORE_LOG_TRACE("Key {0} is released!", (char)eventContext.GetKey());
		return false;
	}
}
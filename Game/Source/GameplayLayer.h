#pragma once

#include<Core/Layer/Layer.h>
#include<Core/Logger/Logger.h>

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer() {}
	~GameplayLayer() {}

	virtual void OnAttach() override {
		LOG_TRACE("GameplayLayer is attached");
	}

	virtual void OnDetach() override {
		LOG_TRACE("GameplayLayer is detached");
	}

	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKey());
		return false;
	}
};

class UILayer : public VIEngine::Layer {
public:
	UILayer() {}
	~UILayer() {}

	virtual void OnAttach() override {
		LOG_TRACE("UILayer is attached");
	}

	virtual void OnDetach() override {
		LOG_TRACE("UILayer is detached");
	}

	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed on UILayer", (char)eventContext.GetKey());
		return true;
	}
	
	virtual bool OnKeyReleasedEvent(const VIEngine::KeyReleasedEvent& eventContext) override {
		if (eventContext.IsKey(VIEngine::EKeyCode::ESCAPE)) {
			LOG_TRACE("ESC key is released");
		}
		return true;
	}

	virtual bool OnMouseButtonPressedEvent(const VIEngine::MouseButtonPressedEvent& eventContext) override {
		if (eventContext.IsButton(VIEngine::EMouseButton::BUTTON_LEFT)) {
			LOG_TRACE("Left mouse button is clicked");
		}
		return true;
	}

};


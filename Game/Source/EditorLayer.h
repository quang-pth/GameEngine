#pragma once

#include<Core/Layer/Layer.h>
#include<Core/Logger/Logger.h>

class UILayer : public VIEngine::Layer {
public:
	UILayer() {}
	~UILayer() {}

	virtual void OnAttach() override {
		LOG_TRACE("UILayer is attached");
	}

	virtual void OnDetach() {
		LOG_TRACE("UILayer is detached");
	}

	virtual void OnProcessInput(const VIEngine::InputState& input) override {
		LOG_TRACE("Key {0} value", input.Keyboard->GetValue(VIEngine::EKeyCode::SPACE));
	}

	virtual void OnUpdate(const VIEngine::Time& time) {
		LOG_TRACE("{0}", time.GetDeltaTime());
	}

	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKeyCode());
		return false;
	}

	virtual bool OnMouseButtonPressedEvent(const VIEngine::MouseButtonPressedEvent& eventContext) override {
		LOG_TRACE("Mouse button is clicked on UILayer");
		return true;
	}
};

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer() {}
	~GameplayLayer() {}

	virtual void OnAttach() override {
		LOG_TRACE("GameplayLayer is attached");
	}

	virtual void OnDetach() {
		LOG_TRACE("GameplayLayer is detached");
	}
	
	virtual void OnProcessInput(const VIEngine::InputState& input) override {
		LOG_TRACE("Key {0} value", input.Keyboard->GetValue(VIEngine::EKeyCode::SPACE));
	}

	virtual void OnUpdate(const VIEngine::Time& time) override {
		LOG_TRACE("{0}", time.GetDeltaTime());
	}

	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKeyCode());
		return false;
	}

	virtual bool OnMouseButtonPressedEvent(const VIEngine::MouseButtonPressedEvent& eventContext) override {
		LOG_TRACE("Mouse button is clicked on GameplayLayer");
		return false;
	}
};


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

	virtual void OnUpdate(VIEngine::Time time) {
		LOG_TRACE("{0} deltaTime", time.GetDeltaTime());
	}

	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKey());
		return false;
	}
};



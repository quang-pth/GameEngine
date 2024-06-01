#pragma once

#include<Core/Layer/Layer.h>

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer();
	~GameplayLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(VIEngine::Time time) override;
	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override;
};

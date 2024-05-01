#pragma once

#include<Core/Layer/Layer.h>

class EditorLayer : public VIEngine::Layer {
public:
	EditorLayer();
	~EditorLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
};


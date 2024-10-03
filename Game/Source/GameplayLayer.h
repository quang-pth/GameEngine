#pragma once

#include<Core/Layer/Layer.h>
#include<Resource/VertexArray.h>
#include<Resource/VertexBuffer.h>
#include<Resource/IndexBuffer.h>
#include<Resource/Shader.h>

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer();
	~GameplayLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(VIEngine::Time time);
	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext);
private:
	VIEngine::VertexArray* mFirstQuad;
	VIEngine::VertexArray* mSecondQuad;
	VIEngine::Shader* mShader;
};

#pragma once

#include<Core/Layer/Layer.h>
#include<Resource/VertexArray.h>
#include<Resource/VertexBuffer.h>
#include<Resource/IndexBuffer.h>
#include<Resource/Shader.h>
#include<Resource/Texture2D.h>

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
	VIEngine::Texture2D* mTexture;
	VIEngine::Texture2D* mTexture2;
};

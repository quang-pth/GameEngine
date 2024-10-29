#pragma once

#include<Core/Layer/Layer.h>
#include<Resource/VertexArray.h>
#include<Resource/VertexBuffer.h>
#include<Resource/IndexBuffer.h>
#include<Resource/Shader.h>
#include<Resource/Texture2D.h>

namespace VIEngine {
	class Animation;
	class Actor;
}

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer();
	~GameplayLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnProcessInput(const VIEngine::InputState&) override;
	virtual void OnUpdate(VIEngine::Time time) override;
	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override;
private:
	VIEngine::VertexArray* mFirstQuad;
	VIEngine::VertexArray* mSecondQuad;
	VIEngine::Shader* mShader;
	VIEngine::Texture2D* mTexture;
	VIEngine::Texture2D* mTexture2;
	class VIEngine::Actor* mActor;
	int8_t mMoveHorizontal = 0, mMoveVertical = 0;
	float mSpeed = 20.0f;
};

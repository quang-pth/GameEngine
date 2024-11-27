#pragma once

#include<Core/Layer/Layer.h>
#include<Resource/VertexArray.h>
#include<Resource/VertexBuffer.h>
#include<Resource/IndexBuffer.h>
#include<Resource/Shader.h>
#include<Resource/Texture2D.h>
#include<Core/Type/Actor.h>

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
	void GenerateTestingAnimations();
	void GenerateTestingSprites();
private:
	class VIEngine::Actor mActor;
	int8_t mMoveHorizontal = 0, mMoveVertical = 0;
	float mSpeed = 5.0f;
};

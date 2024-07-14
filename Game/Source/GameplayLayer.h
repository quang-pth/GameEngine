#pragma once

#include<Core/Layer/Layer.h>

namespace VIEngine {
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
}

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer();
	~GameplayLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(VIEngine::Time time);
	virtual bool OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext);
private:
	class VIEngine::VertexBuffer* mVertexBuffer;
	class VIEngine::IndexBuffer* mIndexBuffer;
	class VIEngine::Shader* mShader;
};

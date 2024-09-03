#include"GameplayLayer.h"
#include<Core/Logger/Logger.h>
#include<Renderer/Renderer.h>

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	// VertexBuffer* vertex = VertexBuffer::Create();
	// IndexBuffer* index = IndexBuffer::Create();
	// Shader* shader = Shader::Create();

	// shader->Bind();
	// vertex->Bind();
	// index->Bind();
	// DrawIndexed(VI_TRIANGLES, index->Count());
}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	VIEngine::Renderer::ClearColor(1.0f, 0.3f, .8f, 1.0f);
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}


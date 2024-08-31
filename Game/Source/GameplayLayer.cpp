#include"GameplayLayer.h"
#include<VIEngine/Base.h>
#include<Core/System/System.h>

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
	
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}


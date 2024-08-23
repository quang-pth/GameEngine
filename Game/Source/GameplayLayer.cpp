#include"GameplayLayer.h"
#include<VIEngine/Base.h>
#include<Core/System/System.h>

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	//VertexBuffer* vertexbuffer = CreateVertexBuffer();
	//IndexBuffer* indexBuffer = CreateIndexBuffer();
	//Shader* shader = CreateShader();

	//vertexBuffer.Bind();
	//indexBuffer.Bind();
	//shader.Bind();
	//DrawQuad();
}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}


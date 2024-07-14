#include"GameplayLayer.h"
#include<VIEngine/Base.h>
#include<Core/System/System.h>

using namespace VIEngine;

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {	
	mVertexBuffer = RendererAPI::CreateVertexBuffer();
	mIndexBuffer = RendererAPI::CreateIndexBuffer();
	mShader = RendererAPI::CreateShader("Assets/Shader/quad.glsl");
}

void GameplayLayer::OnDetach() {
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	static float temp = 0.0f;
	temp += time.GetDeltaTime();

	mRenderer->Submit(RENDER_COMMAND(
		RendererAPI::ClearColor(Math::Sin(temp), 0.5f, Math::Cos(temp));
	));

	mRenderer->Submit(RENDER_COMMAND(
		Vertex vertices[4] = {
			Vertex{Math::Vector3(-0.5f,  0.5f, 0.0f), Math::Vector2(0.0f, 0.0f)},	// top-left
			Vertex{Math::Vector3(-0.5f, -0.5f, 0.0f), Math::Vector2(0.0f, 0.0f)},	// bottom -left
			Vertex{Math::Vector3(0.5f,  -0.5f, 0.0f), Math::Vector2(0.0f, 0.0f)},	// bottom-right
			Vertex{Math::Vector3(0.5f,   0.5f, 0.0f), Math::Vector2(0.0f, 0.0f)}	// top-right
		};
		mVertexBuffer->SetData(vertices, sizeof(vertices) / sizeof(Vertex));

		uint32_t indices[6] = {
			0, 1, 2, // left-bottom triangle
			2, 3, 0 // right-top triangle
		};
		mIndexBuffer->SetData(indices, sizeof(indices) / sizeof(uint32_t));

		RendererAPI::BindShader(mShader);
		RendererAPI::BindVertexBuffer(mVertexBuffer);
		RendererAPI::BindIndexBuffer(mIndexBuffer);
		RendererAPI::DrawIndexed();
	));
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}


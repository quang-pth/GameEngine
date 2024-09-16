#include"GameplayLayer.h"
#include<VIEngine/Base.h>
#include<Renderer/Renderer.h>

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	using namespace VIEngine;

	mVertexBuffer = VertexBuffer::Create();
	mIndexBuffer = IndexBuffer::Create();
	mShader = Shader::Create("Assets/Shader/quad.glsl");

	Vertex vertices[4] = {
		{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // top-left
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // bottom-left
		{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // bottom-right
		{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)} // top-right
	};
	mVertexBuffer->SetData(vertices, sizeof(vertices));

	uint32_t indicies[6] = {
		0, 1, 2, // left-bottom triangle
		2, 3, 0 // right-top triangle
	};
	mIndexBuffer->SetData(indicies, sizeof(indicies), sizeof(indicies) / sizeof(uint32_t));
}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	VIEngine::Renderer::ClearColor(1.0f, 0.3f, 0.6f);

	static float temp = 0.0f;
	temp += time.GetDeltaTime();

	mShader->Bind();
	mShader->SetVector3("tempColor", glm::vec3(glm::cos(temp) + 1.0f, 1.0f, glm::sin(temp) + 1.0f));
	mShader->SetFloat("alpha", glm::sin(temp) + 1.0f);
	mVertexBuffer->Bind();
	mIndexBuffer->Bind();
	VIEngine::Renderer::DrawIndexed(mIndexBuffer->GetNums());
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}


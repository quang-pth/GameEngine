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
		
	mFirstQuad = VertexArray::Create();
	mSecondQuad = VertexArray::Create();
	mShader = Shader::Create("Assets/Shader/quad.glsl");
	mTexture = Texture2D::Create("Assets/horizon-zero-dawn.png");
	mTexture2 = Texture2D::Create("Assets/Sprite/Zero/idle/idle5.png");

	Vertex vertices[4] = {
		{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 2.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // top-left
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // bottom-left
		{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(2.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // bottom-right
		{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(2.0f, 2.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)} // top-right
	};
	uint32_t indicies[6] = {
		0, 1, 2, // left-bottom triangle
		2, 3, 0 // right-top triangle
	};
	mFirstQuad->SetVertexBuffer(vertices, sizeof(vertices));
	mFirstQuad->SetIndexBuffer(indicies, sizeof(indicies), sizeof(indicies) / sizeof(uint32_t));

	Vertex quadVertices[4] = {
		{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)}, // top-left
		{glm::vec3(0.0f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // bottom-left
		{glm::vec3(1.0f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)}, // bottom-right
		{glm::vec3(1.0f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)} // top-right
	};
	mSecondQuad->SetVertexBuffer(quadVertices, sizeof(quadVertices));
	mSecondQuad->SetIndexBuffer(indicies, sizeof(indicies), sizeof(indicies) / sizeof(uint32_t));
}

void GameplayLayer::OnDetach() {
	mFirstQuad->Release();
	mSecondQuad->Release();
	mShader->Release();
	mTexture->Release();

	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	using namespace VIEngine;

	Renderer::ClearColor(1.0f, 0.3f, 0.6f);

	static float temp = 0.0f;
	temp += time.GetDeltaTime();
	
	Renderer::SetAlphaState(true);

	mShader->Bind();
	/*mShader->SetVector3("tempColor", glm::vec3(glm::cos(temp) + 1.0f, 1.0f, glm::sin(temp) + 1.0f));
	mShader->SetFloat("alpha", glm::sin(temp) + 1.0f);
	*/
	mShader->SetVector3("tempColor", glm::vec3(1.0f));
	mShader->SetFloat("alpha", 0.5f);
	mShader->SetInt("image", 0);
	mFirstQuad->Bind();
	mTexture->Bind();
	mTexture->SetWrapMode(ETextureWrapMode::Clamp, ETextureWrapMode::Clamp);
	mTexture->SetBorderColor(1.0f, 0.0f, 0.0f);
	Renderer::DrawIndexed(mFirstQuad->GetIndexBuffer()->GetNums());	

	mSecondQuad->Bind();
	mTexture2->Bind();
	Renderer::DrawIndexed(mSecondQuad->GetIndexBuffer()->GetNums());
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	using namespace VIEngine;
	if (eventContext.IsKey(EKeyCode::NUM_1)) {
		mTexture->SetFilter(ETextureFilter::LinearMipMapLinear, ETextureFilter::Linear);
	}
	else if (eventContext.IsKey(EKeyCode::NUM_2)) {
		mTexture->SetFilter(ETextureFilter::LinearMipMapNearest, ETextureFilter::Linear);
	}
	return false;
}


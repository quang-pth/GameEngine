#include"GameplayLayer.h"
#include<VIEngine/Base.h>
#include<Renderer/Renderer.h>
#include<Core/Component/AnimatorComponent.h>

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
	mTexture = Texture2D::Create("Assets/Sprite/Zero/idle/idle00.png");
	mTexture2 = Texture2D::Create("Assets/test-zero.png");
	
	Animation* idleAnimation = Animation::Create("ZeroIdle");
	idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle00.png");
	idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle01.png");
	idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle02.png");
	idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle03.png");
	idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle04.png");
	idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle05.png");

	Animation* walkBlend = Animation::Create("ZeroWalkBlend");
	walkBlend->AddTexture("Assets/Sprite/Zero/walk/walk-blend.png");

	Animation* walkAnimation = Animation::Create("ZeroWalk");
	//walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk00.png");
	walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk01.png");
	walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk02.png");
	walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk03.png");
	walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk04.png");
	walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk05.png");
	walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk06.png");
	walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk07.png");
	walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk08.png");
	walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk09.png");
	walkAnimation->AddTexture("Assets/Sprite/Zero/walk/walk10.png");
	// actor.GetCompnent<AnimatorComponent>().AddAnimation(anim);
	// actor.GetCompnent<AnimatorComponent>().GetAnimation("ZeroIdle").SetFPS(60);
	mActor = CreateActor();
	AnimatorComponent& animator = mActor->AddComponent<AnimatorComponent>();
	animator.AddAnimation(idleAnimation);
	animator.AddAnimation(walkBlend);
	animator.AddAnimation(walkAnimation);
	animator.SetFPS(60);
	animator.SetActiveAnimation("ZeroWalk");

	Vertex vertices[4] = {
		{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // top-left
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // bottom-left
		{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // bottom-right
		{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)} // top-right
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
	mTexture2->Release();

	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	using namespace VIEngine;

	Renderer::ClearColor(1.0f, 0.3f, 0.6f);

	static float temp = 0.0f;
	temp += time.GetDeltaTime();
	
	Renderer::SetAlphaState(true);

	//mShader->Bind();
	/*mShader->SetVector3("tempColor", glm::vec3(glm::cos(temp) + 1.0f, 1.0f, glm::sin(temp) + 1.0f));
	mShader->SetFloat("alpha", glm::sin(temp) + 1.0f);
	*/
	//mShader->SetVector3("tempColor", glm::vec3(1.0f));
	//mShader->SetFloat("alpha", 0.5f);
	//mShader->SetInt("image", 0);
	//mFirstQuad->Bind();
	//mTexture->Bind();
	//mTexture->SetWrapMode(ETextureWrapMode::Clamp, ETextureWrapMode::Clamp);
	//mTexture->SetBorderColor(1.0f, 0.0f, 0.0f);
	//Renderer::DrawIndexed(mFirstQuad->GetIndexBuffer()->GetNums());

	//mSecondQuad->Bind();
	//mTexture2->Bind();
	//Renderer::DrawIndexed(mSecondQuad->GetIndexBuffer()->GetNums());
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	using namespace VIEngine;
	AnimatorComponent& animator = mActor->GetComponent<AnimatorComponent>();
	if (eventContext.IsKey(EKeyCode::NUM_1)) {
		animator.SetActiveAnimation("ZeroIdle");
	}
	else if (eventContext.IsKey(EKeyCode::NUM_2)) {
		animator.SetActiveAnimation("ZeroWalkBlend");
	}
	else if (eventContext.IsKey(EKeyCode::NUM_3)) {
		animator.SetActiveAnimation("ZeroWalk");
		//animator.SetFlipHorizontal(!animator.GetFlipHorizontal());
	}
	return false;
}


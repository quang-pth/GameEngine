#include"GameplayLayer.h"
#include<Renderer/Renderer.h>
#include<Core/Component/AnimatorComponent.h>
#include<Core/Component/TransformComponent.h>

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

	Animation* walkAnimation = Animation::Create("ZeroWalk");
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

	mActor = CreateActor();

	AnimatorComponent& animator = mActor.AddComponent<AnimatorComponent>();
	animator.AddAnimation(idleAnimation);
	animator.AddAnimation(walkAnimation);
	animator.SetFPS(120);
	animator.SetActiveAnimation(walkAnimation->GetName());

	for (uint8_t i = 0; i < 10; i++) {
		for (uint8_t j = 0; j < 10; j++) {
			Animation* idleAnimation = Animation::Create("ZeroIdle[" + std::to_string(i) + ", " + std::to_string(j) + "]");
			idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle00.png");
			idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle01.png");
			idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle02.png");
			idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle03.png");
			idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle04.png");
			idleAnimation->AddTexture("Assets/Sprite/Zero/idle/idle05.png");

			Animation* walkAnimation = Animation::Create("ZeroWalk[" + std::to_string(i) + ", " + std::to_string(j) + "]");
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

			Actor actor2 = CreateActor();
			TransformComponent& transformComponent = actor2.GetComponent<TransformComponent>();
			transformComponent.SetPositionX(-10.0f + j * 2.0f + 1.0f);
			transformComponent.SetPositionY(10.0f - i * 2.0f - 1.0f);
			AnimatorComponent& animator2 = actor2.AddComponent<AnimatorComponent>();
			animator2.AddAnimation(walkAnimation);
			animator2.SetFPS(120);
		}
	}

	//Vertex vertices[4] = {
	//	{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // top-left
	//	{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // bottom-left
	//	{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // bottom-right
	//	{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)} // top-right
	//};
	//uint32_t indicies[6] = {
	//	0, 1, 2, // left-bottom triangle
	//	2, 3, 0 // right-top triangle
	//};
	//mFirstQuad->SetVertexBuffer(vertices, sizeof(vertices));
	//mFirstQuad->SetIndexBuffer(indicies, sizeof(indicies), sizeof(indicies) / sizeof(uint32_t));

	//Vertex quadVertices[4] = {
	//	{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)}, // top-left
	//	{glm::vec3(0.0f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // bottom-left
	//	{glm::vec3(1.0f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)}, // bottom-right
	//	{glm::vec3(1.0f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)} // top-right
	//};
	//mSecondQuad->SetVertexBuffer(quadVertices, sizeof(quadVertices));
	//mSecondQuad->SetIndexBuffer(indicies, sizeof(indicies), sizeof(indicies) / sizeof(uint32_t));
}

void GameplayLayer::OnDetach() {
	mFirstQuad->Release();
	mSecondQuad->Release();
	mShader->Release();
	mTexture->Release();
	mTexture2->Release();

	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnProcessInput(const VIEngine::InputState& inputState) {
	using namespace VIEngine;

	mMoveHorizontal = 0;
	mMoveVertical = 0;

	AnimatorComponent& animator = mActor.GetComponent<AnimatorComponent>();
	if (inputState.Keyboard->IsPressed(EKeyCode::LEFT) || inputState.Keyboard->IsPressed(EKeyCode::A)) {
		mMoveHorizontal += -1;
		animator.SetFlipHorizontal(true);
	}
	if (inputState.Keyboard->IsPressed(EKeyCode::RIGHT) || inputState.Keyboard->IsPressed(EKeyCode::D)) {
		mMoveHorizontal += 1;
		animator.SetFlipHorizontal(false);
	}
	if (inputState.Keyboard->IsPressed(EKeyCode::DOWN) || inputState.Keyboard->IsPressed(EKeyCode::S)) {
		mMoveVertical += -1;
	}
	if (inputState.Keyboard->IsPressed(EKeyCode::UP) || inputState.Keyboard->IsPressed(EKeyCode::W)) {
		mMoveVertical += 1;
	}

	if (mMoveHorizontal == 0) {
		animator.SetActiveAnimation("ZeroIdle");
		animator.SetFPS(24);
	}
	else {
		animator.SetActiveAnimation("ZeroWalk");
		animator.SetFPS(60);
	}
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	using namespace VIEngine;

	Renderer::ClearColor(1.0f, 0.3f, 0.6f);

	static float temp = 0.0f;
	temp += time.GetDeltaTime();
	
	Renderer::SetAlphaState(true);

	TransformComponent& transform = mActor.GetComponent<TransformComponent>();
	transform.SetPositionX(transform.GetPosition().x + mMoveHorizontal * mSpeed * time.GetDeltaTime());
	transform.SetPositionY(transform.GetPosition().y + mMoveVertical * mSpeed * time.GetDeltaTime());

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
	return false;
}


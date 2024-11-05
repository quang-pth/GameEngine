#include"GameplayLayer.h"
#include<Renderer/Renderer.h>
#include<Core/Component/AnimatorComponent.h>
#include<Core/Component/TransformComponent.h>
#include<Resource/Sprite.h>

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

	using namespace VIEngine;

	for (uint8_t i = 0; i < 10; i++) {
		for (uint8_t j = 0; j < 10; j++) {
			Animation* idleAnimation2 = Animation::Create("ZeroIdle[" + std::to_string(i) + ", " + std::to_string(j) + "]");
			idleAnimation2->AddSprite("Assets/Sprite/Zero/idle/idle00.png");
			idleAnimation2->AddSprite("Assets/Sprite/Zero/idle/idle01.png");
			idleAnimation2->AddSprite("Assets/Sprite/Zero/idle/idle02.png");
			idleAnimation2->AddSprite("Assets/Sprite/Zero/idle/idle03.png");
			idleAnimation2->AddSprite("Assets/Sprite/Zero/idle/idle04.png");
			idleAnimation2->AddSprite("Assets/Sprite/Zero/idle/idle05.png");

			Animation* walkAnimation2 = Animation::Create("ZeroWalk[" + std::to_string(i) + ", " + std::to_string(j) + "]");
			walkAnimation2->AddSprite("Assets/Sprite/Zero/walk/walk01.png");
			walkAnimation2->AddSprite("Assets/Sprite/Zero/walk/walk02.png");
			walkAnimation2->AddSprite("Assets/Sprite/Zero/walk/walk03.png");
			walkAnimation2->AddSprite("Assets/Sprite/Zero/walk/walk04.png");
			walkAnimation2->AddSprite("Assets/Sprite/Zero/walk/walk05.png");
			walkAnimation2->AddSprite("Assets/Sprite/Zero/walk/walk06.png");
			walkAnimation2->AddSprite("Assets/Sprite/Zero/walk/walk07.png");
			walkAnimation2->AddSprite("Assets/Sprite/Zero/walk/walk08.png");
			walkAnimation2->AddSprite("Assets/Sprite/Zero/walk/walk09.png");
			walkAnimation2->AddSprite("Assets/Sprite/Zero/walk/walk10.png");

			Actor actor2 = CreateActor();
			TransformComponent& transformComponent = actor2.GetComponent<TransformComponent>();
			transformComponent.SetPositionX(-10.0f + j * 2.0f + 1.0f);
			transformComponent.SetPositionY(10.0f - i * 2.0f - 1.0f);
			AnimatorComponent& animator2 = actor2.AddComponent<AnimatorComponent>();
			
			if (j % 2 == 0) {
				animator2.AddAnimation(idleAnimation2);
				animator2.SetFPS(24);
			}
			else {
				animator2.AddAnimation(walkAnimation2);
				animator2.SetFPS(120);
			}
		}
	}

	Animation* idleAnimation = Animation::Create("ZeroIdle");
	idleAnimation->AddSprite("Assets/Sprite/Zero/idle/idle00.png");
	idleAnimation->AddSprite("Assets/Sprite/Zero/idle/idle01.png");
	idleAnimation->AddSprite("Assets/Sprite/Zero/idle/idle02.png");
	idleAnimation->AddSprite("Assets/Sprite/Zero/idle/idle03.png");
	idleAnimation->AddSprite("Assets/Sprite/Zero/idle/idle04.png");
	idleAnimation->AddSprite("Assets/Sprite/Zero/idle/idle05.png");

	Animation* walkAnimation = Animation::Create("ZeroWalk");
	walkAnimation->AddSprite("Assets/Sprite/Zero/walk/walk01.png");
	walkAnimation->AddSprite("Assets/Sprite/Zero/walk/walk02.png");
	walkAnimation->AddSprite("Assets/Sprite/Zero/walk/walk03.png");
	walkAnimation->AddSprite("Assets/Sprite/Zero/walk/walk04.png");
	walkAnimation->AddSprite("Assets/Sprite/Zero/walk/walk05.png");
	walkAnimation->AddSprite("Assets/Sprite/Zero/walk/walk06.png");
	walkAnimation->AddSprite("Assets/Sprite/Zero/walk/walk07.png");
	walkAnimation->AddSprite("Assets/Sprite/Zero/walk/walk08.png");
	walkAnimation->AddSprite("Assets/Sprite/Zero/walk/walk09.png");
	walkAnimation->AddSprite("Assets/Sprite/Zero/walk/walk10.png");

	mActor = CreateActor();

	AnimatorComponent& animator = mActor.AddComponent<AnimatorComponent>();
	animator.AddAnimation(idleAnimation);
	animator.AddAnimation(walkAnimation);
	animator.SetFPS(120);
	animator.SetActiveAnimation(walkAnimation->GetName());
}

void GameplayLayer::OnDetach() {
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

	//if (mMoveHorizontal == 0) {
	//	animator.SetActiveAnimation("ZeroIdle");
	//	animator.SetFPS(24);
	//}
	//else {
	//	animator.SetActiveAnimation("ZeroWalk");
	//	animator.SetFPS(120);
	//}
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


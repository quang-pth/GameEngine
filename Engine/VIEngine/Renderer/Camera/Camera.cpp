#include"Camera.h"
#include"Core/Input/KeyCode.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace VIEngine {
	const float mPI = 3.14159f;

	Camera::Camera(const glm::mat4& projectionMatrix) : mProjectionMatrix(projectionMatrix) {
		mPanSpeed = 0.0015f;
		mRotationSpeed = 0.002f;
		mZoomSpeed = 0.2f;

		mPosition = { 0, 0, -0.1f};
		mRotation = glm::vec3(0.0f, 0.0f, 0.0f);

		mFocalPoint = glm::vec3(0.0f);
		mDistance = glm::distance(mPosition, mFocalPoint);

		mYaw = 0.0f;
		mPitch = 0.0f;
	}

	Camera::~Camera() {

	}

	void Camera::ProcessInput(const InputState& inputState) {
		//if (inputState.Mouse->IsPressed(EKeyCode::LEFT_ALT))
		//{
		//	const glm::vec2& currentMousePosition{ Input::GetMouseX(), Input::GetMouseY() };
		//	glm::vec2 delta = currentMousePosition - mPreviousMousePosition;
		//	mPreviousMousePosition = currentMousePosition;

		//	if (Input::IsMousePressed(LIGHT_MOUSE_BUTTON_MIDDLE))
		//		MousePan(delta);
		//	else if (Input::IsMousePressed(LIGHT_MOUSE_BUTTON_LEFT))
		//		MouseRotate(delta);
		//	else if (Input::IsMousePressed(LIGHT_MOUSE_BUTTON_RIGHT))
		//		MouseZoom(delta.y);
		//}
	}

	void Camera::Update() {
		mPosition = CalculatePosition();
		glm::quat orientation = GetOrientation();
		mRotation = glm::eulerAngles(orientation) * (180.0f / (float)mPI);
		mViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 1)) * glm::toMat4(glm::conjugate(orientation)) * glm::translate(glm::mat4(1.0f), -mPosition);
	}

	void Camera::Focus() {

	}

	glm::vec3 Camera::GetUpDirection() {
		return glm::rotate(GetOrientation(), AxisUnitY);
	}

	glm::vec3 Camera::GetRightDirection() {
		return glm::rotate(GetOrientation(), AxisUnitX);
	}

	glm::vec3 Camera::GetForwardDirection() {
		return glm::rotate(GetOrientation(), AxisUnitZ);
	}

	void Camera::MousePan(const glm::vec2& delta) {
		mFocalPoint += -GetRightDirection() * delta.x * mPanSpeed * mDistance;
		mFocalPoint += GetUpDirection() * delta.y * mPanSpeed * mDistance;
	}

	void Camera::MouseRotate(const glm::vec2& delta) {
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		mYaw += yawSign * delta.x * mRotationSpeed;
		mPitch += delta.y * mRotationSpeed;
	}

	void Camera::MouseZoom(float delta) {
		mDistance -= delta * mZoomSpeed;
		if (mDistance < 1.0f)
		{
			mFocalPoint += GetForwardDirection();
			mDistance = 1.0f;
		}
	}

	glm::vec3 Camera::CalculatePosition() {
		return mFocalPoint - GetForwardDirection() * mDistance;
	}

	glm::quat Camera::GetOrientation() {
		return glm::quat(glm::vec3(-mPitch, -mYaw, 0));
	}
}
#include"InputState.h"

#include<GLFW/glfw3.h>

namespace VIEngine {
	static EKeyState GLFWToEngineKeyState(int32_t action) {
		if (action == GLFW_PRESS) return EKeyState::Pressed;
		if (action == GLFW_REPEAT) return EKeyState::Held;
		if (action == GLFW_RELEASE) return EKeyState::Released;
		return EKeyState::None;
	}

	GLFWKeyboardInput::GLFWKeyboardInput(void* window) {
		mWindow = (GLFWwindow*)window;
	}

	EKeyState GLFWKeyboardInput::GetState(int32_t keyCode) const {
		return GLFWToEngineKeyState(glfwGetKey(mWindow, keyCode));
	}

	bool GLFWKeyboardInput::IsPressed(int32_t keyCode) const {
		return glfwGetKey(mWindow, keyCode) == GLFW_PRESS;
	}
	
	bool GLFWKeyboardInput::IsHeld(int32_t keyCode) const {
		// TODO: Not use this method, it not work on GLFW
		return glfwGetKey(mWindow, keyCode) == GLFW_REPEAT;
	}

	bool GLFWKeyboardInput::IsReleased(int32_t keyCode) const {
		return glfwGetKey(mWindow, keyCode) == GLFW_RELEASE;
	}
	
	GLFWMouseInput::GLFWMouseInput(void* window) {
		mWindow = (GLFWwindow*)window;
	}

	EKeyState GLFWMouseInput::GetState(int32_t button) const { 
		return GLFWToEngineKeyState(glfwGetMouseButton(mWindow, button));
	}
	
	bool GLFWMouseInput::IsPressed(int32_t button) const {
		return glfwGetMouseButton(mWindow, button) == GLFW_PRESS;
	}
	
	bool GLFWMouseInput::IsHeld(int32_t button) const {
		// TODO: Not use this method, it not work on GLFW
		return glfwGetMouseButton(mWindow, button) == GLFW_REPEAT;
	}
	
	bool GLFWMouseInput::IsReleased(int32_t button) const {
		return glfwGetMouseButton(mWindow, button) == GLFW_RELEASE;
	}
}
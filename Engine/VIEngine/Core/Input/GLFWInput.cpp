#pragma once

#include"InputState.h"
#include"Core/Logger/Logger.h"
#include<GLFW/glfw3.h>

namespace VIEngine {
	static EKeyState GLFWToEngineKeyState(int32_t glfwAction) {
		if (glfwAction == GLFW_PRESS) return EKeyState::Pressed;
		if (glfwAction == GLFW_REPEAT) return EKeyState::Held;
		if (glfwAction == GLFW_RELEASE) return EKeyState::Released;
		return EKeyState::None;
	}

	/* |-----------------------------------------|
	/* |-------------KEYBOARD INPUT--------------|
	/* |-----------------------------------------|
	*/
	GLFWKeyboardInput::GLFWKeyboardInput(void* window) : mWindow((GLFWwindow*)window) {

	}

	EKeyState GLFWKeyboardInput::GetState(int32_t keyCode) const {
		int32_t keyState = glfwGetKey(mWindow, keyCode);
		return GLFWToEngineKeyState(keyState);
	}
	
	bool GLFWKeyboardInput::IsPressed(int32_t keyCode) const {
		return glfwGetKey(mWindow, keyCode) == GLFW_PRESS;
	}
	
	bool GLFWKeyboardInput::IsHeld(int32_t keyCode) const {
		//TODO: Fix later - CORE_LOG_WARN("GLFW not support for held event through class method, use an event listener to the KeyHeldEvent instead");
		return glfwGetKey(mWindow, keyCode) == GLFW_REPEAT;
	}
	
	bool GLFWKeyboardInput::IsReleased(int32_t keyCode) const {
		return glfwGetKey(mWindow, keyCode) == GLFW_RELEASE;
	}

	/* |-----------------------------------------|
	/* |---------------MOUSE INPUT---------------|
	/* |-----------------------------------------|
	*/
	GLFWMouseInput::GLFWMouseInput(void* window) : mWindow((GLFWwindow*)window) {

	}

	EKeyState GLFWMouseInput::GetState(int32_t button) const {
		int32_t keyState = glfwGetMouseButton(mWindow, button);
		return GLFWToEngineKeyState(keyState);
	}

	bool GLFWMouseInput::IsPressed(int32_t button) const {
		return glfwGetMouseButton(mWindow, button) == GLFW_PRESS;
	}

	bool GLFWMouseInput::IsHeld(int32_t button) const {
		//TODO: Fix later - CORE_LOG_WARN("GLFW not support for held event through class method, use an event listener to the MouseButtonHeldEvent instead");
		return glfwGetMouseButton(mWindow, button) == GLFW_REPEAT;
	}

	bool GLFWMouseInput::IsReleased(int32_t button) const {
		return glfwGetMouseButton(mWindow, button) == GLFW_RELEASE;
	}
}
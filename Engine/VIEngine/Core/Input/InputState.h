#pragma once

#include"KeyCode.h"

class GLFWwindow;

namespace VIEngine {
	class VI_API KeyboardInput {
	public:
		virtual ~KeyboardInput() = default;

		VI_FORCE_INLINE int8_t GetValue(EKeyCode keyCode) const { return (IsPressed(keyCode) || IsHeld(keyCode)) ? 1 : 0; }
		VI_FORCE_INLINE EKeyState GetState(EKeyCode keyCode) const { return GetState((int32_t)keyCode); }
		VI_FORCE_INLINE bool IsPressed(EKeyCode keyCode) const { return IsPressed((int32_t)keyCode); }
		VI_FORCE_INLINE bool IsHeld(EKeyCode keyCode) const { return IsHeld((int32_t)keyCode); }
		VI_FORCE_INLINE bool IsReleased(EKeyCode keyCode) const { return IsReleased((int32_t)keyCode); }
		
		virtual EKeyState GetState(int32_t keyCode) const = 0;
		virtual bool IsPressed(int32_t keyCode) const = 0;
		virtual bool IsHeld(int32_t keyCode) const = 0;
		virtual bool IsReleased(int32_t keyCode) const = 0;
	protected:
		KeyboardInput() = default;
	};

	class VI_API GLFWKeyboardInput : public KeyboardInput {
	public:
		GLFWKeyboardInput(void* window);
		virtual EKeyState GetState(int32_t keyCode) const override;
		virtual bool IsPressed(int32_t keyCode) const override;
		virtual bool IsHeld(int32_t keyCode) const override;
		virtual bool IsReleased(int32_t keyCode) const override;
	private:
		GLFWwindow* mWindow;
	};

	struct MouseInputData {
		float X = 0.0f, Y = 0.0f;
		float OffsetX = 0.0f, OffsetY = 0.0f;
		float ScrollX = 0.0f, ScrollY = 0.0f;
	};

	class VI_API MouseInput {
	public:
		virtual ~MouseInput() = default;
		VI_FORCE_INLINE int8_t GetValue(EMouseButton button) const { return (IsPressed(button) || IsHeld(button)) ? 1 : 0; }
		VI_FORCE_INLINE EKeyState GetState(EMouseButton button) const { return GetState((int32_t)button); }
		VI_FORCE_INLINE bool IsPressed(EMouseButton button) const { return IsPressed((int32_t)button); }
		VI_FORCE_INLINE bool IsHeld(EMouseButton button) const { return IsHeld((int32_t)button); }
		VI_FORCE_INLINE bool IsReleased(EMouseButton button) const { return IsReleased((int32_t)button); }

		virtual EKeyState GetState(int32_t button) const = 0;
		virtual bool IsPressed(int32_t button) const = 0;
		virtual bool IsHeld(int32_t button) const = 0;
		virtual bool IsReleased(int32_t button) const = 0;
		virtual const MouseInputData& GetData() const = 0;
		virtual void SetPosition(float x, float y) = 0;
		virtual void SetPositionX(float x) = 0;
		virtual void SetPositionY(float y) = 0;
		virtual void SetScroll(float scrollX, float scrollY) = 0;
		virtual void SetScrollX(float scrollX) = 0;
		virtual void SetScrollY(float scrollY) = 0;
		virtual void SetOffset(float offsetX, float offsetY) = 0;
		virtual void SetOffsetX(float offsetX) = 0;
		virtual void SetOffsetY(float offsetY) = 0;
	protected:
		MouseInput() = default;
	};

	class VI_API GLFWMouseInput : public MouseInput {
	public:
		GLFWMouseInput(void* window);
		virtual EKeyState GetState(int32_t button) const override;
		virtual bool IsPressed(int32_t button) const override;
		virtual bool IsHeld(int32_t button) const override;
		virtual bool IsReleased(int32_t button) const override;
		VI_FORCE_INLINE virtual const MouseInputData& GetData() const override { return mData; }
		virtual void SetPosition(float x, float y) override { mData.X = x; mData.Y = y; }
		virtual void SetPositionX(float x) override { mData.X = x; }
		virtual void SetPositionY(float y) override { mData.Y = y; }
		virtual void SetScroll(float scrollX, float scrollY) override { mData.ScrollX = scrollX; mData.ScrollY = scrollY; }
		virtual void SetScrollX(float scrollX) override { mData.ScrollX = scrollX; }
		virtual void SetScrollY(float scrollY) override { mData.ScrollY = scrollY; }
		virtual void SetOffset(float offsetX, float offsetY) override { mData.OffsetX = offsetX; mData.OffsetY = offsetY; }
		virtual void SetOffsetX(float offsetX) override { mData.OffsetX = offsetX; }
		virtual void SetOffsetY(float offsetY) override { mData.OffsetY = offsetY; }
	private:
		GLFWwindow* mWindow;
		MouseInputData mData;
	};

	struct VI_API InputState {
		KeyboardInput* Keyboard;
		MouseInput* Mouse;
	};
}
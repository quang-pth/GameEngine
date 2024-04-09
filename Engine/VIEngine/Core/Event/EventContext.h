#pragma once

#include"pch.h"
#include"Core/Input/KeyCode.h"

#define IS_KEY VI_FORCE_INLINE bool IsKey(EKeyCode keyCode) const { return mKeyCode == (int32_t)keyCode; } 
#define IS_BUTTON VI_FORCE_INLINE bool IsButton(EMouseButton button) const { return mButton == (int32_t)button; } 

namespace VIEngine {
	class VI_API EventContext {
	public:
		virtual ~EventContext() = default;
	};

	class VI_API WindowResizedEvent : public EventContext {
	public:
		WindowResizedEvent(int32_t width, int32_t height) : mWidth(width), mHeight(height) {}
		VI_FORCE_INLINE int32_t GetWidth() const { return mWidth; }
		VI_FORCE_INLINE int32_t GetHeight() const { return mHeight; }
	private:
		int32_t mWidth, mHeight;
	};

	class VI_API KeyPressedEvent : public EventContext {
	public:
		KeyPressedEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VI_FORCE_INLINE int32_t GetKey() const { return mKeyCode; }
		IS_KEY
	private:
		int32_t mKeyCode;
	};

	class VI_API KeyHeldEvent : public EventContext {
	public:
		KeyHeldEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VI_FORCE_INLINE int32_t GetKey() const { return mKeyCode; }
		IS_KEY
	private:
		int32_t mKeyCode;
	};

	class VI_API KeyReleasedEvent : public EventContext {
	public:
		KeyReleasedEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VI_FORCE_INLINE int32_t GetKey() const { return mKeyCode; }
		IS_KEY
	private:
		int32_t mKeyCode;
	};

	class VI_API MouseMovedEvent : public EventContext {
	public:
		MouseMovedEvent(double x, double y, double offsetX, double offsetY) : 
			xPosition(x), yPosition(y),
			xOffset(offsetX), yOffset(offsetY) {}
		VI_FORCE_INLINE double GetPositionX() const { return xPosition; }
		VI_FORCE_INLINE double GetPositionY() const { return yPosition; }
		VI_FORCE_INLINE double GetOffsetX() const { return xOffset; }
		VI_FORCE_INLINE double GetOffsetY() const { return yOffset; }
	private:
		double xPosition, yPosition;
		double xOffset, yOffset;
	};

	class VI_API MouseScrolledEvent : public EventContext {
	public:
		MouseScrolledEvent(double offsetX, double offsetY) : xOffset(offsetX), yOffset(offsetY) {}
		VI_FORCE_INLINE double GetScrollX() const { return xOffset; }
		VI_FORCE_INLINE double GetScrollY() const { return yOffset; }
	private:
		double xOffset, yOffset;
	};

	class VI_API MouseButtonPressedEvent : public EventContext {
	public:
		MouseButtonPressedEvent(int32_t button) : mButton(button) {}
		VI_FORCE_INLINE int32_t GetButton() const { return mButton; }
		IS_BUTTON
	private:
		int32_t mButton;
	};

	class VI_API MouseButtonHeldEvent : public EventContext {
	public:
		MouseButtonHeldEvent(int32_t button) : mButton(button) {}
		VI_FORCE_INLINE int32_t GetButton() const { return mButton; }
		IS_BUTTON
	private:
		int32_t mButton;
	};

	class VI_API MouseButtonReleasedEvent : public EventContext {
	public:
		MouseButtonReleasedEvent(int32_t button) : mButton(button) {}
		VI_FORCE_INLINE int32_t GetButton() const { return mButton; }
		IS_BUTTON
	private:
		int32_t mButton;
	};
}
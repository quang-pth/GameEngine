#pragma once

#include"pch.h"

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
		VI_FORCE_INLINE int32_t GetKeyCode() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	};

	class VI_API KeyHeldEvent : public EventContext {
	public:
		KeyHeldEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VI_FORCE_INLINE int32_t GetKeyCode() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	};

	class VI_API KeyReleasedEvent : public EventContext {
	public:
		KeyReleasedEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VI_FORCE_INLINE int32_t GetKeyCode() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	};

	class VI_API MouseMovedEvent : public EventContext {
	public:
		MouseMovedEvent(double x, double y, double offsetX, double offsetY) : 
			xPosition(x), yPosition(y),
			xOffset(offsetX), yOffset(offsetY) {}
		VI_FORCE_INLINE double GetX() const { return xPosition; }
		VI_FORCE_INLINE double GetY() const { return yPosition; }
		VI_FORCE_INLINE double GetOffsetX() const { return xOffset; }
		VI_FORCE_INLINE double GetOffsetY() const { return yOffset; }
	private:
		double xPosition, yPosition;
		double xOffset, yOffset;
	};

	class VI_API MouseScrolledEvent : public EventContext {
	public:
		MouseScrolledEvent(double offsetX, double offsetY) : xOffset(offsetX), yOffset(offsetY) {}
		VI_FORCE_INLINE double GetOffsetX() const { return xOffset; }
		VI_FORCE_INLINE double GetOffsetY() const { return yOffset; }
	private:
		double xOffset, yOffset;
	};

	class VI_API MouseButtonPressedEvent : public EventContext {
	public:
		MouseButtonPressedEvent(int32_t button) : mButton(button) {}
		VI_FORCE_INLINE int32_t GetButton() const { return mButton; }
	private:
		int32_t mButton;
	};

	class VI_API MouseButtonHeldEvent : public EventContext {
	public:
		MouseButtonHeldEvent(int32_t button) : mButton(button) {}
		VI_FORCE_INLINE int32_t GetButton() const { return mButton; }
	private:
		int32_t mButton;
	};

	class VI_API MouseButtonReleasedEvent : public EventContext {
	public:
		MouseButtonReleasedEvent(int32_t button) : mButton(button) {}
		VI_FORCE_INLINE int32_t GetButton() const { return mButton; }
	private:
		int32_t mButton;
	};
}
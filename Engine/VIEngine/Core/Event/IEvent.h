#pragma once

#include"pch.h"

namespace VIEngine {
	template<typename T> using EventCallback = std::function<bool(const T&)>;

	class VI_API IEvent {
	public:
		virtual ~IEvent() = default;
	};

	class VI_API WindowResizedEvent : public IEvent {
	public:
		WindowResizedEvent(int32_t width, int32_t height) : mWidth(width), mHeight(height) {}
		VI_FORCE_INLINE int32_t GetWidth() const { return mWidth; }
		VI_FORCE_INLINE int32_t GetHeight() const { return mHeight; }
	private:
		int32_t mWidth, mHeight;
	};
	
	class VI_API KeyPressedEvent : public IEvent {
	public:
		KeyPressedEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VI_FORCE_INLINE int32_t GetKey() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	};

	class VI_API KeyHeldEvent : public IEvent {
	public:
		KeyHeldEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VI_FORCE_INLINE int32_t GetKey() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	};

	class VI_API KeyRelasedEvent : public IEvent {
	public:
		KeyRelasedEvent(int32_t keyCode) : mKeyCode(keyCode) {}
		VI_FORCE_INLINE int32_t GetKey() const { return mKeyCode; }
	private:
		int32_t mKeyCode;
	};
	
	class VI_API MousePressedEvent : public IEvent {
	public:
		MousePressedEvent(int32_t button) : mButton(button) {}
		VI_FORCE_INLINE int32_t GetButton() const { return mButton; }
	private:
		int32_t mButton;
	};
	
	class VI_API MouseHeldEvent : public IEvent {
	public:
		MouseHeldEvent(int32_t button) : mButton(button) {}
		VI_FORCE_INLINE int32_t GetButton() const { return mButton; }
	private:
		int32_t mButton;
	};

	class VI_API MouseReleasedEvent : public IEvent {
	public:
		MouseReleasedEvent(int32_t button) : mButton(button) {}
		VI_FORCE_INLINE int32_t GetButton() const { return mButton; }
	private:
		int32_t mButton;
	};

	class VI_API MouseMovedEvent : public IEvent {
	public:
		MouseMovedEvent(double xPosition, double yPosition) : mX(xPosition), mY(yPosition) {}
		VI_FORCE_INLINE double GetX() const { return mX; }
		VI_FORCE_INLINE double GetY() const { return mY; }
	private:
		double mX, mY;
	};
	
	class VI_API MouseScrolledEvent : public IEvent {
	public:
		MouseScrolledEvent(double xOffset, double yOffset) : mOffsetX(xOffset), mOffsetY(yOffset) {}
		VI_FORCE_INLINE double GetOffsetX() const { return mOffsetX; }
		VI_FORCE_INLINE double GetOffsetY() const { return mOffsetY; }
	private:
		double mOffsetX, mOffsetY;
	};
}
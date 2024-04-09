#pragma once

#include"pch.h"
#include"Core/Event/EventContext.h"

namespace VIEngine {
	class VI_API Layer {
	public:
		Layer() {
			mID = GetUUID();
		}

		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnProcessInput(const struct InputState&) {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual bool OnWindowResizedEvent(const WindowResizedEvent&) { return false; }
		virtual bool OnKeyPressedEvent(const KeyPressedEvent&) { return false; }
		virtual bool OnKeyHeldEvent(const KeyHeldEvent&) { return false; }
		virtual bool OnKeyReleasedEvent(const KeyReleasedEvent&) { return false; }
		virtual bool OnMouseMovedEvent(const MouseMovedEvent&) { return false; }
		virtual bool OnMouseScrolledEvent(const MouseScrolledEvent&) { return false; }
		virtual bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent&) { return false; }
		virtual bool OnMouseButtonHeldEvent(const MouseButtonHeldEvent&) { return false; }
		virtual bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent&) { return false; }
	private:
		UUID mID;
	};

}
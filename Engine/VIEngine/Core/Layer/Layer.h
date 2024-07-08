#pragma once

#include"pch.h"
#include"Core/Event/EventContext.h"
#include"Core/Time/Time.h"
#include"Scene/Scene.h"

namespace VIEngine {
	class VI_API Layer {
	public:
		Layer();
		Layer(Shared<Scene> scene);

		virtual ~Layer() = default;

		VI_FORCE_INLINE Shared<Scene> GetScene() const { return mScene; }
		VI_FORCE_INLINE void SetScene(const Shared<Scene>& scene) { mScene = scene; }

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnProcessInput(const struct InputState&) {}
		virtual void OnUpdate(Time time) {}
		virtual void OnRender(Time time) {}
		virtual bool OnWindowResizedEvent(const WindowResizedEvent&) { return false; }
		virtual bool OnKeyPressedEvent(const KeyPressedEvent&) { return false; }
		virtual bool OnKeyHeldEvent(const KeyHeldEvent&) { return false; }
		virtual bool OnKeyReleasedEvent(const KeyReleasedEvent&) { return false; }
		virtual bool OnMouseMovedEvent(const MouseMovedEvent&) { return false; }
		virtual bool OnMouseScrolledEvent(const MouseScrolledEvent&) { return false; }
		virtual bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent&) { return false; }
		virtual bool OnMouseButtonHeldEvent(const MouseButtonHeldEvent&) { return false; }
		virtual bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent&) { return false; }
	protected:
		Shared<Scene> mScene;
	private:
		UUID mID;
	};

}
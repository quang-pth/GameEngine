#pragma once

#include"pch.h"
#include"Core/Time.h"
#include"Core/Input/InputState.h"
#include"Core/Event/EventContext.h"

namespace VIEngine {
    class VI_API Layer {
    public:
        Layer() : mEnabled(true) {}
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnProcessInput(const InputState&) {}
        virtual void OnUpdate(const Time&) {}
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
        
        VI_FORCE_INLINE void SetEnabled(bool value) { mEnabled = value; }
        VI_FORCE_INLINE bool IsEnabled() const { return mEnabled; }
    protected:
        bool mEnabled;
    };
}
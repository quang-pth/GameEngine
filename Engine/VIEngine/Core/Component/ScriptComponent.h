#pragma once

#include"ECS/IComponent.h"
#include"Core/Type/Actor.h"
#include"Core/Time/Time.h"
#include<VIScript/LuaExecutor.h>
#include<VIScript/LuaModule.h>

namespace VIEngine {
	class VI_API ScriptComponent : public ECS::Component<ScriptComponent, Actor> {
	public:
		DECLARE_RTTI
	public:
		ScriptComponent() = default;
		ScriptComponent(const std::string& filepath);
		~ScriptComponent();
		void OnStart();
		void OnProcessInput(const struct InputState&);
		void OnUpdate(Time time);
		void OnDestroyed();
		void OnKeyPressedEvent(const class KeyPressedEvent& eventContext);
		void OnMouseButtonPressedEvent(const class MouseButtonPressedEvent& eventContext);
	private:
		std::vector<std::string> SplitString(const std::string& str, const std::string& delimeter);
	private:
		LuaExecutor* mExecutor;
		LuaModule* mModule;
		std::string mFilepath;
		std::string mObjectName;
	};
}
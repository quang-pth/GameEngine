#pragma once

#include"Core/Type/RTTI.h"
#include"ECS/ISystem.h"

namespace VIEngine {
	class VI_API ScriptSystem : public ECS::System<ScriptSystem> {
	public:
		DECLARE_RTTI
	public:
		ScriptSystem() = default;
		ScriptSystem(ECS::SystemID id, ECS::ESystemPriority priority = ECS::ESystemPriority::Low);
		~ScriptSystem();
		virtual void OnInit() override;
		virtual void OnShutdown() override;
		virtual void OnStart() override;
		void OnProcessInput(const struct InputState&);
		virtual void OnUpdate(Time) override;
		virtual void OnDestroyed() override;
		void OnKeyPressedEvent(const class KeyPressedEvent& eventContext);

		VI_FORCE_INLINE class LuaExecutor* GetLuaExecutor() const { return mLuaExecutor; }
		VI_FORCE_INLINE class IStateHandler* GetStateHandler() const { return mStateHandler; }

	private:
		class LuaExecutor* mLuaExecutor;
		class IStateHandler* mStateHandler;
	};
}
#include"ScriptSystem.h"
#include"Core/Application.h"
#include"Core/Component/ScriptComponent.h"
#include"Core/Input/InputState.h"
#include"Core/Event/EventContext.h"
#include"Animation/AnimationLuaModule.h"
#include"VIScript/LuaModuleExporter.hpp"
#include"Animation/Animation.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(ScriptSystem)

	ScriptSystem::ScriptSystem(ECS::SystemID id, ECS::ESystemPriority priority) 
		: ECS::System<ScriptSystem>(id, priority)
	{

	}

	ScriptSystem::~ScriptSystem() {

	}

	void ScriptSystem::OnInit() {
		static auto animModule = LuaModuleExporter<Animation>::Create(AnimationLuaModule::ModuleDef);
		mStateHandler = new LuaStateHandler();
		mLuaExecutor = new LuaExecutor(mStateHandler);
		mLuaExecutor->RegisterModule(&animModule);
	}

	void ScriptSystem::OnShutdown() {
		VI_FREE_MEMORY(mLuaExecutor);
	}

	void ScriptSystem::OnStart() {
		for (ScriptComponent* scriptComponent : mCoordinator->GetComponentArray<ScriptComponent>()) {
			scriptComponent->OnStart();
		}
	}

	void ScriptSystem::OnProcessInput(const InputState& inputState) {
		for (ScriptComponent* scriptComponent : mCoordinator->GetComponentArray<ScriptComponent>()) {
			scriptComponent->OnProcessInput(inputState);
		}
	}

	void ScriptSystem::OnUpdate(Time time) {
		for (ScriptComponent* scriptComponent : mCoordinator->GetComponentArray<ScriptComponent>()) {
			scriptComponent->OnUpdate(time);
		}
	}

	void ScriptSystem::OnDestroyed() {
		for (ScriptComponent* scriptComponent : mCoordinator->GetComponentArray<ScriptComponent>()) {
			scriptComponent->OnDestroyed();
		}
	}

	void ScriptSystem::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
		for (ScriptComponent* scriptComponent : mCoordinator->GetComponentArray<ScriptComponent>()) {
			scriptComponent->OnKeyPressedEvent(eventContext);
		}
	}
}
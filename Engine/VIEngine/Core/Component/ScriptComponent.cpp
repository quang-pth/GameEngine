#include"ScriptComponent.h"
#include"ScriptModule.h"
#include<VIScript/Lua.hpp>
#include"Core/Input/InputState.h"
#include"Core/Event/EventContext.h"
#include"Core/Input/InputStateLuaModule.h"
#include"Core/System/ScriptSystem.h"
#include"Core/Application.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(ScriptComponent)

	ScriptComponent::ScriptComponent(const std::string& filepath) 
		: mFilepath(filepath)
	{
		std::vector<std::string> tokens = SplitString(mFilepath, "/");
		tokens = SplitString(tokens[tokens.size() - 1], ".");
		mObjectName = tokens[0];
	}

	ScriptComponent::~ScriptComponent() {
	}

	void ScriptComponent::OnStart() {
		// Init the script module to ensure that the UUID is already gerenated in the constructor
		mModule = new ScriptModule(mObjectName, GetOwner().GetID());
		mExecutor = Application::Get().GetSystem<ScriptSystem>().GetLuaExecutor();
		mExecutor->RegisterModule(mModule);
		mExecutor->ExecuteFromFile(mFilepath);
	}

	void ScriptComponent::OnProcessInput(const InputState& inputState) {
		mExecutor->InvokeTableFunction(mObjectName, "OnProcessInput", true, LuaUserData::Create(
			(void*)&inputState,
			InputStateLuaModule::ModuleDef.GetMetableName(),
			InputStateLuaModule::ModuleDef.GetRegs(),
			InputStateLuaModule::ModuleDef.GetAttributes()
			)
		);
	}

	void ScriptComponent::OnUpdate(Time time) {
		mExecutor->InvokeTableFunction(mObjectName, "OnUpdate", true, LuaNumber::Create(time.GetDeltaTime()));
	}

	void ScriptComponent::OnDestroyed() {
	}

	void ScriptComponent::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
		mExecutor->InvokeTableFunction(mObjectName, "OnKeyPressed", true, LuaNumber::Create(eventContext.GetKey()));
	}

	std::vector<std::string> ScriptComponent::SplitString(const std::string& str, const std::string& delimeter) {
		std::vector<std::string> tokens;
		size_t currentPosition = 0;
		size_t previousPosition = 0;

		while ((currentPosition = str.find(delimeter, previousPosition)) != std::string::npos) {
			std::string token = str.substr(previousPosition, currentPosition - previousPosition);
			tokens.push_back(token);
			previousPosition = currentPosition + delimeter.length();
		}

		// Push the last token
		tokens.push_back(str.substr(previousPosition));

		return tokens;
	}
}
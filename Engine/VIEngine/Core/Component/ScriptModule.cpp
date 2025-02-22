#include"ScriptModule.h"
#include"Core/Type/Actor.h"
#include"Core/Application.h"
#include"TransformComponent.h"
#include"ScriptComponent.h"
#include"AnimatorComponent.h"
#include"AnimatorLuaModule.h"
#include"Core/System/ScriptSystem.h"

namespace VIEngine {
	ScriptModule::ScriptModule() {

	}
	
	ScriptModule::ScriptModule(const std::string& objectName, ECS::EntityID actorID) : mObjectName(objectName), mActorID(actorID) {

	}

	ScriptModule::~ScriptModule() {

	}

	Actor GetActor(lua_State* L) {
		return CreateActor(lua_tointeger(L, lua_upvalueindex(1)));
	}

	LuaExecutor* GetExecutor(lua_State* L) {
		return reinterpret_cast<LuaExecutor*>(lua_touserdata(L, lua_upvalueindex(2)));
	}

	int lua_GetPosition(lua_State* L) {
		Actor actor = GetActor(L);

		TransformComponent& transform = actor.GetComponent<TransformComponent>();
		
		lua_pushnumber(L, transform.GetPosition().x);
		lua_pushnumber(L, transform.GetPosition().y);
		lua_pushnumber(L, transform.GetPosition().z);

		return 3;
	}

	int lua_SetPositionX(lua_State* L) {
		Actor actor = GetActor(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TNUMBER && "Actor:SetPositionX #2 argument required a number");

		TransformComponent& transform = actor.GetComponent<TransformComponent>();
		float x = lua_tonumber(L, 2);
		transform.SetPositionX(x);
		
		return 0;
	}

	int lua_SetPositionY(lua_State* L) {
		Actor actor = GetActor(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TNUMBER && "Actor:SetPositionY #2 argument required a number");

		TransformComponent& transform = actor.GetComponent<TransformComponent>();
		float y = lua_tonumber(L, 2);
		transform.SetPositionY(y);

		return 0;
	}

	int lua_GetAnimator(lua_State* L) {
		Actor actor = GetActor(L);
		LuaExecutor* executor = GetExecutor(L);

		AnimatorComponent& animator = actor.GetComponent<AnimatorComponent>();
		executor->PushValue(LuaUserData::Create(
			&animator, 
			AnimatorLuaModule::ModuleDef.GetMetableName(), 
			AnimatorLuaModule::ModuleDef.GetRegs(),
			AnimatorLuaModule::ModuleDef.GetAttributes()
		));

		return 1;
	}

	const std::vector<luaL_Reg> regs = {
		{"GetPosition", lua_GetPosition},
		{"SetPositionX", lua_SetPositionX},
		{"SetPositionY", lua_SetPositionY},
		{"GetAnimator", lua_GetAnimator},
		{NULL, NULL}
	};

	const std::vector<luaL_Reg>& ScriptModule::Regs() const {
		return regs;
	}

	int32_t ScriptModule::PushUpValues(lua_State* L) const {
		lua_pushinteger(L, mActorID);
		lua_pushlightuserdata(L, Application::Get().GetSystem<ScriptSystem>().GetLuaExecutor());
		return 2;
	}
}
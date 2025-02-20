#pragma once

#include"pch.h"
#include<VIScript/Lua.hpp>
#include<VIScript/LuaModule.h>
#include"ECS/EntityManager.h"

namespace VIEngine {
	class ScriptModule : public LuaModule {
	public:
		ScriptModule();
		ScriptModule(const std::string& objectName, ECS::EntityID actorID);
		virtual ~ScriptModule();
		// Export C++ instance to lua as table name
		virtual const std::string& LuaName() const override { return mObjectName; }
		// Export C++ functions to lua
		virtual const std::vector<luaL_Reg>& Regs() const override;
		virtual int32_t PushUpValues(lua_State*) const override;
	private:
		std::string mObjectName;
		ECS::EntityID mActorID;
	};
}
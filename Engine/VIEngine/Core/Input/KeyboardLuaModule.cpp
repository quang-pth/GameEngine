#include"KeyboardLuaModule.h"

namespace VIEngine {
	const std::string NAME = "KeyboardInput";
	const std::string META_TABLE_NAME = "KeyboardInput.MetaTable";

	GLFWKeyboardInput* GetObject(lua_State* L) {
		return *reinterpret_cast<GLFWKeyboardInput**>(luaL_checkudata(L, 1, META_TABLE_NAME.c_str()));
	}

	int lua_IsPressed(lua_State* L) {
		GLFWKeyboardInput* obj = GetObject(L);

		int numArgs = lua_gettop(L);
		VI_ASSERT(numArgs == 2 && "IsPressed function required only 1 arguments to be passed in as a number");

		int keyCode = lua_tointeger(L, 2);
		int isPressed = obj->IsPressed(keyCode);

		lua_pushboolean(L, isPressed);

		return 1;
	}

	LuaModuleDef<GLFWKeyboardInput> KeyboardLuaModule::ModuleDef
		= LuaModuleDef<GLFWKeyboardInput>
	{
		NAME,
		{
			{"IsPressed", lua_IsPressed},
			{NULL, NULL}
		},
		[](lua_State* L) -> GLFWKeyboardInput* {
			VI_ASSERT(false && "Invalid function call");
			return nullptr;
		},
		[](GLFWKeyboardInput* obj) -> void {
			VI_ASSERT(false && "Invalid function call");
		}
	};
}
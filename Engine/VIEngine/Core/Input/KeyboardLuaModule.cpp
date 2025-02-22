#include"KeyboardLuaModule.h"

namespace VIEngine {
	const std::string NAME = "KeyboardInput";
	const std::string META_TABLE_NAME = "KeyboardInput.MetaTable";

	GLFWKeyboardInput* GetObject(lua_State* L) {
		return *reinterpret_cast<GLFWKeyboardInput**>(luaL_checkudata(L, 1, META_TABLE_NAME.c_str()));
	}

	int lua_IsKeyboardPressed(lua_State* L) {
		GLFWKeyboardInput* keyboard = GetObject(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TNUMBER && "Keyboard:IsPressed #2 argument required an integer");

		lua_pushboolean(L, keyboard->IsPressed(lua_tointeger(L, 2)));

		return 1;
	}
	
	int lua_IsKeyboardHeld(lua_State* L) {
		GLFWKeyboardInput* keyboard = GetObject(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TNUMBER && "Keyboard:IsHeld #2 argument required an integer");

		lua_pushboolean(L, keyboard->IsHeld(lua_tointeger(L, 2)));

		return 1;
	}
	
	int lua_IsKeyboardReleased(lua_State* L) {
		GLFWKeyboardInput* keyboard = GetObject(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TNUMBER && "Keyboard:IsReleased #2 argument required an integer");

		lua_pushboolean(L, keyboard->IsReleased(lua_tointeger(L, 2)));

		return 1;
	}

	LuaModuleDef<GLFWKeyboardInput> KeyboardLuaModule::ModuleDef
		= LuaModuleDef<GLFWKeyboardInput>
	{
		NAME,
		{
			{"IsPressed", lua_IsKeyboardPressed},
			{"IsHeld", lua_IsKeyboardHeld},
			{"IsReleased", lua_IsKeyboardReleased},
			{NULL, NULL}
		},
		{},
		[](lua_State* L) -> GLFWKeyboardInput* {
			VI_ASSERT(false && "Invalid function call");
			return nullptr;
		},
		[](GLFWKeyboardInput* obj) -> void {
			VI_ASSERT(false && "Invalid function call");
		}
	};
}
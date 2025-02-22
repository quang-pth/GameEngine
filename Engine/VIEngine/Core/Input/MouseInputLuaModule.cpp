#include"MouseInputLuaModule.h"

namespace VIEngine
{
    const std::string NAME = "MouseInput";

    MouseInput* GetObject(lua_State* L) {
        return *reinterpret_cast<MouseInput**>(lua_touserdata(L, 1));
    }

    int lua_GetMousePositionX(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        lua_pushnumber(L, mouseInput->GetPositionX());

        return 1;
    }

    int lua_GetMousePositionY(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        lua_pushnumber(L, mouseInput->GetPositionY());

        return 1;
    }

    int lua_GetMousePosition(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        lua_pushnumber(L, mouseInput->GetPositionX());
        lua_pushnumber(L, mouseInput->GetPositionY());

        return 2;
    }

    int lua_GetScrollX(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        lua_pushnumber(L, mouseInput->GetScrollX());

        return 1;
    }

    int lua_GetScrollY(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        lua_pushnumber(L, mouseInput->GetScrollY());

        return 1;
    }

    int lua_GetScroll(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        lua_pushnumber(L, mouseInput->GetScrollX());
        lua_pushnumber(L, mouseInput->GetScrollY());

        return 2;
    }

    int lua_GetOffsetX(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        lua_pushnumber(L, mouseInput->GetOffsetX());

        return 1;
    }

    int lua_GetOffsetY(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        lua_pushnumber(L, mouseInput->GetOffsetY());

        return 1;
    }

    int lua_GetOffset(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        lua_pushnumber(L, mouseInput->GetOffsetX());
        lua_pushnumber(L, mouseInput->GetOffsetY());

        return 2;
    }

    int lua_IsMousePressed(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TNUMBER && "MouseInput:IsPressed #2 argument required a number");

        lua_pushboolean(L, mouseInput->IsPressed(lua_tonumber(L, 2)));

        return 1;
    }

    int lua_IsMouseHeld(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TNUMBER && "MouseInput:IsHeld #2 argument required a number");

        lua_pushboolean(L, mouseInput->IsHeld(lua_tonumber(L, 2)));

        return 1;
    }

    int lua_IsMouseReleased(lua_State* L) {
        MouseInput* mouseInput = GetObject(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TNUMBER && "MouseInput:IsHeld #2 argument required a number");

        lua_pushboolean(L, mouseInput->IsReleased(lua_tonumber(L, 2)));

        return 1;
    }

    LuaModuleDef<MouseInput> MouseInputLuaModule::ModuleDef =
        LuaModuleDef<MouseInput>
    {
        NAME,
        {
            {"GetPositionX", lua_GetMousePositionX},
            {"GetPositionY", lua_GetMousePositionY},
            {"GetPosition", lua_GetMousePosition},
            {"GetScrollX", lua_GetScrollX},
            {"GetScrollY", lua_GetScrollY},
            {"GetScroll", lua_GetScroll},
            {"GetOffsetX", lua_GetOffsetX},
            {"GetOffsetY", lua_GetOffsetY},
            {"GetOffset", lua_GetOffset},
            {"IsPressed", lua_IsMousePressed},
            {"IsHeld", lua_IsMouseHeld},
            {"IsReleased", lua_IsMouseReleased},
            {NULL, NULL}
        },
        {},
        [](lua_State* L) -> MouseInput* {
            VI_ASSERT(false && "Should not be called in lua side");
            return nullptr;
        },
        [](MouseInput* obj) -> void {
            VI_ASSERT(false && "Should not be called in lua side");
        }
    };
} // namespace VIEngine
#include"Box2DLuaModule.h"
#include"VIScript/LuaExecutor.h"

namespace VIEngine {
    const std::string NAME = "Box2DComponent";
    
    Box2DComponent* GetBox2DComponent(lua_State* L) {
		return *reinterpret_cast<Box2DComponent**>(lua_touserdata(L, 1));
	}

	static LuaExecutor* GetExecutor(lua_State* L) {
		return reinterpret_cast<LuaExecutor*>(lua_touserdata(L, lua_upvalueindex(1)));
	}

    int lua_Box2DGetWidth(lua_State* L) {
        Box2DComponent* box = GetBox2DComponent(L);

        lua_pushnumber(L, box->GetWidth());

        return 1;
    }

    int lua_Box2DSetWidth(lua_State* L) {
        Box2DComponent* box = GetBox2DComponent(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TNUMBER && "Box2DComponent:SetWidth #2 argument required a number");

        box->SetWidth(lua_tonumber(L, 2));

        return 0;
    }

    int lua_Box2DGetHeight(lua_State* L) {
        Box2DComponent* box = GetBox2DComponent(L);

        lua_pushnumber(L, box->GetHeight());

        return 1;
    }

    int lua_Box2DSetHeight(lua_State* L) {
        Box2DComponent* box = GetBox2DComponent(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TNUMBER && "Box2DComponent:SetHeight #2 argument required a number");

        box->SetHeight(lua_tonumber(L, 2));

        return 0;
    }

    LuaModuleDef<Box2DComponent> Box2DLuaModule::ModuleDef =
        LuaModuleDef<Box2DComponent>
    {
        NAME,
        {
            {"GetWidth", lua_Box2DGetWidth},
            {"SetWidth", lua_Box2DSetWidth},
            {"GetHeight", lua_Box2DGetHeight},
            {"SetHeight", lua_Box2DSetHeight},
            {NULL, NULL}
        },
        {},
        [](lua_State* L) -> Box2DComponent* {
            VI_ASSERT(false);
            return nullptr;
        },
        [](Box2DComponent* obj) -> void {
            VI_ASSERT(false);
        }
    };
}
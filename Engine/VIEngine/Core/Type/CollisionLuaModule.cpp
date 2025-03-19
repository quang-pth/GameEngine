#include"CollisionLuaModule.h"

namespace VIEngine {
    const std::string NAME = "Collision";

    Collision* GetCollision(lua_State* L) {
        return *reinterpret_cast<Collision**>(lua_touserdata(L, 1));
    }

    int lua_GetContactCount(lua_State* L) {
        Collision* collision = GetCollision(L);

        lua_pushnumber(L, collision->ContactCount);

        return 1;
    }

    LuaModuleDef<Collision> CollisionLuaModule::ModuleDef = 
        LuaModuleDef<Collision>
    {
        NAME,
        {
            {"GetContactCount", lua_GetContactCount},
            {NULL, NULL}
        },
        {},
        [](lua_State* L) -> Collision* {
            VI_ASSERT(false);
            return nullptr;
        },
        [](Collision* obj) -> void {
            VI_ASSERT(false);
        }
    };
}
#include"RigidBodyLuaModule.h"

namespace VIEngine
{
    const std::string NAME = "RigidBodyComponent";

    RigidBodyComponent* GetRigidBodyComponent(lua_State* L) {
        return *reinterpret_cast<RigidBodyComponent**>(lua_touserdata(L, 1));
    }

    int lua_GetBodyType(lua_State* L) {
        RigidBodyComponent* rigidBody = GetRigidBodyComponent(L);

        lua_pushnumber(L, (int)rigidBody->GetBodyType());

        return 1;
    }

    int lua_SetBodyType(lua_State* L) {
        RigidBodyComponent* rigidBody = GetRigidBodyComponent(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TNUMBER && "RigidBodyComponent:SetBodyType #2 argument required a number");

        int bodyType = lua_tonumber(L, 2);
        if (bodyType == 0) {
            rigidBody->SetBodyType(EBodyType::STATIC);
        }
        else if (bodyType == 1) {
            rigidBody->SetBodyType(EBodyType::DYNAMIC);
        }
        else if (bodyType == 2) {
            rigidBody->SetBodyType(EBodyType::KINEMATIC);
        }
        else {
            VI_ASSERT(false && "Invalid body type specified for #2 argument in RigidBodyComponent:SetBodyType");
        }

        return 0;
    }

    int lua_GetGravityScale(lua_State* L) {
        RigidBodyComponent* rigidBody = GetRigidBodyComponent(L);

        lua_pushnumber(L, rigidBody->GetGravityScale());

        return 1;
    }

    int lua_SetGravityScale(lua_State* L) {
        RigidBodyComponent* rigidBody = GetRigidBodyComponent(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TNUMBER && "RigidBodyComponent:SetGravityScale #2 argument required a number");

        rigidBody->SetGravityScale(lua_tonumber(L, 2));

        return 0;
    }

    LuaModuleDef<RigidBodyComponent> RigidBodyLuaModule::ModuleDef =
        LuaModuleDef<RigidBodyComponent>
    {
        NAME,
        {
            {"GetBodyType", lua_GetBodyType},
            {"SetBodyType", lua_SetBodyType},
            {"GetGravityScale", lua_GetGravityScale},
            {"SetGravityScale", lua_SetGravityScale},
            {NULL, NULL}
        },
        {},
        [](lua_State* L) -> RigidBodyComponent* {
            VI_ASSERT(false);
            return nullptr;
        },
        [](RigidBodyComponent* obj) -> void {
            VI_ASSERT(false);
        }
    };
} // namespace VIEngine

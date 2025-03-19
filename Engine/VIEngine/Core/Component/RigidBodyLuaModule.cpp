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

    int lua_ApplyForceToCenter(lua_State* L) {
        RigidBodyComponent* rigidBody = GetRigidBodyComponent(L);

        // Apply force X
        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TNUMBER && "RigidBodyComponent:ApplyForceToCenter #2 argument required a number");
        
        // Apply force Y
        type = lua_type(L, 3);
        VI_ASSERT(type == LUA_TNUMBER && "RigidBodyComponent:ApplyForceToCenter #3 argument required a number");
        
        bool awake = true;
        if (lua_gettop(L) == 4) {
            type = lua_type(L, 4);
            VI_ASSERT(type == LUA_TBOOLEAN && "RigidBodyComponent:ApplyForceToCenter #4 argument required a boolean");
            awake = lua_toboolean(L, 4);
        }

        float accelerationX = lua_tonumber(L, 2);
        b2Body_ApplyForceToCenter(
            rigidBody->GetBodyID(), 
            b2Vec2{PixelToWorld(lua_tonumber(L, 2)), PixelToWorld(lua_tonumber(L, 3))}, 
            awake
        );
        
        return 0;
    }

    int lua_GetLinearVelocity(lua_State* L) {
        RigidBodyComponent* rigidBody = GetRigidBodyComponent(L);
        
        lua_pushnumber(L, PixelToWorld(b2Body_GetLinearVelocity(rigidBody->GetBodyID()).x));
        lua_pushnumber(L, PixelToWorld(b2Body_GetLinearVelocity(rigidBody->GetBodyID()).y));

        return 2;
    }

    int lua_SetLinearDamping(lua_State* L) {
        RigidBodyComponent* rigidBody = GetRigidBodyComponent(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TNUMBER && "RigidBodyComponent::SetLinearDamping #2 argument required a number");

        float damping = StaticCast<float>(lua_tonumber(L, 2));
        rigidBody->SetLinearDamping(damping);
        if (b2Body_IsValid(rigidBody->GetBodyID())) {
            b2Body_SetLinearDamping(rigidBody->GetBodyID(), damping);
        }

        return 0;
    }

    int lua_GetLinearDamping(lua_State* L) {
        RigidBodyComponent* rigidBody = GetRigidBodyComponent(L);

        lua_pushnumber(L, rigidBody->GetLinearDamping());

        return 1;
    }

    int lua_SetFixedRotation(lua_State* L) {
        RigidBodyComponent* rigidBody = GetRigidBodyComponent(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TBOOLEAN && "RigidBodyComponent::SetFixedRotation #2 argument required a number");

        rigidBody->SetFixedRotation(lua_toboolean(L, 2));
        if (b2Body_IsValid(rigidBody->GetBodyID())) {
            b2Body_SetFixedRotation(rigidBody->GetBodyID(), lua_toboolean(L, 2));
        }

        return 0;
    }

    int lua_GetFixedRotation(lua_State* L) {
        RigidBodyComponent* rigidBody = GetRigidBodyComponent(L);

        lua_pushboolean(L, rigidBody->GetFixedRotation());

        return 1;
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
            {"ApplyForceToCenter", lua_ApplyForceToCenter},
            {"GetLinearVelocity", lua_GetLinearVelocity},
            {"SetLinearDamping", lua_SetLinearDamping},
            {"GetLinearDamping", lua_GetLinearDamping},
            {"SetFixedRotation", lua_SetFixedRotation},
            {"GetFixedRotation", lua_GetFixedRotation},
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

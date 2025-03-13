#include"AnimationLuaModule.h"
#include"VIScript/LuaExecutor.h"
#include"Core/Application.h"
#include"Core/System/ScriptSystem.h"
#include"Resource/Sprite.h"
#include"Resource/Texture2D.h"

namespace VIEngine
{
    const std::string NAME = "Animation";

    Animation* GetObject(lua_State* L) {
        return *reinterpret_cast<Animation**>(lua_touserdata(L, 1));
    }

    static LuaExecutor* GetExecutor(lua_State* L) {
        return reinterpret_cast<LuaExecutor*>(lua_touserdata(L, lua_upvalueindex(1)));
    }

    int lua_AddAnimationSprite(lua_State* L) {
        Animation* anim = GetObject(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TSTRING && "Animation:AddSprite #2 argument required a string");

        anim->AddSprite(lua_tostring(L, 2));

        return 0;
    }

    int lua_GetAnimationName(lua_State* L) {
        Animation* anim = GetObject(L);
        LuaExecutor* executor = GetExecutor(L);

        executor->PushValue(LuaString::Create(anim->GetName()));

        return 1;
    }

    int lua_SetAnimationName(lua_State* L) {
        Animation* anim = GetObject(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TSTRING && "Animation:SetName #2 argument required a string");

        anim->SetName(lua_tostring(L, 2));

        return 0;        
    }

    int lua_GetAnimationNumsFrame(lua_State* L) {
        Animation* anim = GetObject(L);
        LuaExecutor* executor = GetExecutor(L);

        executor->PushValue(LuaInteger::Create(anim->GetNumsFrame()));

        return 1;
    }

    int lua_SetAnimationIsLoop(lua_State* L) {
        Animation* anim = GetObject(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TBOOLEAN && "Animation:SetIsLoop #2 argument required a boolean");
        
        anim->SetIsLoop(lua_toboolean(L, 2));

        return 0;
    }

    int lua_GetAnimationIsLoop(lua_State* L) {
        Animation* anim = GetObject(L);

        lua_pushboolean(L, anim->GetIsLoop());

        return 1;
    }

    LuaModuleDef<Animation> AnimationLuaModule::ModuleDef =
        LuaModuleDef<Animation>
    {
        NAME,
        {
            {"AddSprite", lua_AddAnimationSprite},
            {"GetName", lua_GetAnimationName},
            {"SetName", lua_SetAnimationName},
            {"GetNumsFrame", lua_GetAnimationNumsFrame},
            {"SetIsLoop", lua_SetAnimationIsLoop},
            {"GetIsLoop", lua_GetAnimationIsLoop},
            {NULL, NULL}
        },
        {},
        [](lua_State* L) -> Animation* {
            int type = lua_type(L, 1);
            VI_ASSERT(type == LUA_TSTRING && "Animation.Create #1 required a string");
            return Animation::Create(lua_tostring(L, 1));
        },
        [](Animation* obj) -> void {
            // Let's C++ side handle
            // TODO: later
            //obj->Release();
        },
        [](lua_State* L) -> int { // Push upvalues function
            LuaExecutor* executor = Application::Get().GetSystem<ScriptSystem>().GetLuaExecutor();
            lua_pushlightuserdata(L, executor);
            return 1;
        }
    };
} // namespace VIEngine

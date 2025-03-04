#include"SpriteLuaModule.h"
#include"VIScript/LuaExecutor.h"
#include"Resource/Sprite.h"

namespace VIEngine {
    const std::string NAME = "SpriteComponent";

    static SpriteComponent* GetSpriteComponent(lua_State* L) {
		return *reinterpret_cast<SpriteComponent**>(lua_touserdata(L, 1));
	}

	static LuaExecutor* GetExecutor(lua_State* L) {
		return reinterpret_cast<LuaExecutor*>(lua_touserdata(L, lua_upvalueindex(1)));
	}

    static int lua_SetSprite(lua_State* L) {
        SpriteComponent* spriteComponent = GetSpriteComponent(L);

        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TSTRING && "Sprite:SetSprite #2 argument required a string");

        spriteComponent->SetSprite(lua_tostring(L, 2));

        return 0;
    }

    static int lua_SetColor(lua_State* L) {
        SpriteComponent* spriteComponent = GetSpriteComponent(L);
        
        // Check R component
        int type = lua_type(L, 2);
        VI_ASSERT(type == LUA_TSTRING && "Sprite:SetColor #2 argument required a number");
        float r = lua_tonumber(L, 2);
        // Check G component
        type = lua_type(L, 3);
        VI_ASSERT(type == LUA_TSTRING && "Sprite:SetColor #3 argument required a number");
        float g = lua_tonumber(L, 3);
        // Check B component
        type = lua_type(L, 4);
        VI_ASSERT(type == LUA_TSTRING && "Sprite:SetColor #4 argument required a number");
        float b = lua_tonumber(L, 4);
        // Check A component
        float a = spriteComponent->GetSprite()->GetColor().a;
        type = lua_type(L, 5);
        if (type != LUA_TNIL) {
            a = lua_tonumber(L, 5);
        }
        
        spriteComponent->SetColor({r, g, b, a});

        return 0;
    }

    static int lua_FlipHorizontal(lua_State* L) {
		SpriteComponent* spriteComponent = GetSpriteComponent(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TBOOLEAN && "SpriteComponent:FlipHorizontal #2 argument required a boolean");

		bool flipHorizontal = lua_toboolean(L, 2);
		spriteComponent->SetFlipHorizontal(flipHorizontal);

		return 0;
	}

	static int lua_FlipVertical(lua_State* L) {
		SpriteComponent* spriteComponent = GetSpriteComponent(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TBOOLEAN && "SpriteComponent:FlipVertical #2 argument required a boolean");

		bool flipVertical = lua_toboolean(L, 2);
		spriteComponent->SetFlipVertical(flipVertical);

		return 0;
	}

    LuaModuleDef<SpriteComponent> SpriteLuaModule::ModuleDef = 
        LuaModuleDef<SpriteComponent>
        {
            NAME,
            {
                {"SetSprite", lua_SetSprite},
                {"SetColor", lua_SetColor},
                {"FlipHorizontal", lua_FlipHorizontal},
                {"FlipVertical", lua_FlipVertical},
                {NULL, NULL}
            },
            {},
            [](lua_State* L) -> SpriteComponent* {
                VI_ASSERT(false);
                return nullptr;
            },
            [](SpriteComponent* obj) -> void {
                VI_ASSERT(false);
            }
        };
}
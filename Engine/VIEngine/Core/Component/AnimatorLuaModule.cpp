#include"AnimatorLuaModule.h"
#include"VIScript/LuaExecutor.h"

namespace VIEngine {
	const std::string NAME = "AnimatorComponent";
	
	AnimatorComponent* GetAnimatorComponent(lua_State* L) {
		return *reinterpret_cast<AnimatorComponent**>(lua_touserdata(L, 1));
	}

	static LuaExecutor* GetExecutor(lua_State* L) {
		return reinterpret_cast<LuaExecutor*>(lua_touserdata(L, lua_upvalueindex(1)));
	}

	int lua_FlipHorizontal(lua_State* L) {
		AnimatorComponent* animator = GetAnimatorComponent(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TBOOLEAN && "AnimatorComponent:FlipHorizontal #2 argument required a boolean");

		bool flipHorizontal = lua_toboolean(L, 2);
		animator->SetFlipHorizontal(flipHorizontal);

		return 0;
	}

	int lua_FlipVertical(lua_State* L) {
		AnimatorComponent* animator = GetAnimatorComponent(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TBOOLEAN && "AnimatorComponent:FlipVertical #2 argument required a boolean");

		bool flipVertical = lua_toboolean(L, 2);
		animator->SetFlipVertical(flipVertical);

		return 0;
	}

	int lua_SetActiveAnimation(lua_State* L) {
		AnimatorComponent* animator = GetAnimatorComponent(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TSTRING && "AnimatorComponent:SetActiveAnimation #2 argument required a string");

		const char* animationName = lua_tostring(L, 2);
		animator->SetActiveAnimation(animationName);

		return 0;
	}

	int lua_SetFPS(lua_State* L) {
		AnimatorComponent* animator = GetAnimatorComponent(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TNUMBER && "AnimatorComponent:SetFPS #2 argument required a number");
		animator->SetFPS(lua_tonumber(L, 2));

		return 0;
	}

	int lua_AddAnimation(lua_State* L) {
		AnimatorComponent* animator = GetAnimatorComponent(L);

		int type = lua_type(L, 2);
		VI_ASSERT(type == LUA_TUSERDATA && "Animation:AddSprite #2 argument required an animation table");

		Animation* anim = *reinterpret_cast<Animation**>(lua_touserdata(L, 2));
		animator->AddAnimation(anim);

		return 0;
	}

	LuaModuleDef<AnimatorComponent> AnimatorLuaModule::ModuleDef =
		LuaModuleDef<AnimatorComponent>
	{
		NAME,
		{ // regs
			{"FlipHorizontal", lua_FlipHorizontal},
			{"FlipVertical", lua_FlipVertical},
			{"SetActiveAnimation", lua_SetActiveAnimation},
			{"SetFPS", lua_SetFPS},
			{"AddAnimation", lua_AddAnimation},
			{NULL, NULL}
		},
		{}, // index attributes
		[](lua_State* L) -> AnimatorComponent* { // constructor
			VI_ASSERT(false);
			return nullptr;
		},
		[](AnimatorComponent* obj) -> void { // garbage collection
			VI_ASSERT(false);
		}
	};
}
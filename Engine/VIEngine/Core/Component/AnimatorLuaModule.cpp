#include"AnimatorLuaModule.h"

namespace VIEngine {
	const std::string NAME = "AnimatorComponent";
	
	AnimatorComponent* GetAnimatorComponent(lua_State* L) {
		return *reinterpret_cast<AnimatorComponent**>(lua_touserdata(L, 1));
	}

	int lua_FlipHorizontal(lua_State* L) {
		AnimatorComponent* animator = GetAnimatorComponent(L);

		bool flipHorizontal = lua_toboolean(L, 1);
		animator->SetFlipHorizontal(flipHorizontal);

		return 0;
	}

	LuaModuleDef<AnimatorComponent> AnimatorLuaModule::ModuleDef =
		LuaModuleDef<AnimatorComponent>
	{
		NAME,
		{
			{"FlipX", lua_FlipHorizontal},
			{NULL, NULL}
		},
		[](lua_State* L) -> AnimatorComponent* {
			VI_ASSERT(false);
			return nullptr;
		},
		[](AnimatorComponent* obj) -> void {
			VI_ASSERT(false);
		}
	};
}
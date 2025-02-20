#pragma once

#include"VIScript/LuaModule.h"
#include"AnimatorComponent.h"

namespace VIEngine {
	class AnimatorLuaModule {
	public:
		static LuaModuleDef<AnimatorComponent> ModuleDef;
	};
}
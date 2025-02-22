#pragma once

#include"InputState.h"
#include"VIScript/LuaModule.h"

namespace VIEngine {
	class MouseInputLuaModule {
	public:
		static LuaModuleDef<MouseInput> ModuleDef;
	};
}
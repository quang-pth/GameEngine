#pragma once

#include"InputState.h"
#include"VIScript/LuaModule.h"

namespace VIEngine {
	class KeyboardLuaModule {
	public:
		static LuaModuleDef<GLFWKeyboardInput> ModuleDef;
	};
}
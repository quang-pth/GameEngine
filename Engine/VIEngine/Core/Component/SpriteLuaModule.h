#pragma once

#include"VIScript/LuaModule.h"
#include"SpriteComponent.h"

namespace VIEngine {
	class SpriteLuaModule {
	public:
		static LuaModuleDef<SpriteComponent> ModuleDef;
	};
}
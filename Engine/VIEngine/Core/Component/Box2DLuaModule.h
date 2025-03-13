#pragma once

#include"VIScript/LuaModule.h"
#include"Box2DComponent.h"

namespace VIEngine {
	class Box2DLuaModule {
	public:
		static LuaModuleDef<Box2DComponent> ModuleDef;
	};
}
#pragma once

#include"VIScript/LuaModule.h"
#include"RigidBodyComponent.h"

namespace VIEngine {
	class RigidBodyLuaModule {
	public:
		static LuaModuleDef<RigidBodyComponent> ModuleDef;
	};
}
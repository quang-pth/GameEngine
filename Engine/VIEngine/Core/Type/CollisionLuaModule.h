#pragma once

#include<VIScript/LuaModule.h>
#include"Collision.h"

namespace VIEngine {
    class CollisionLuaModule {
    public:
        static LuaModuleDef<Collision> ModuleDef;
    };
}
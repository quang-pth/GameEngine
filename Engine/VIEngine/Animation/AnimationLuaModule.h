#pragma once

#include"VIScript/LuaModule.h"
#include"Animation.h"

namespace VIEngine {
    class AnimationLuaModule {
    public:
        static LuaModuleDef<Animation> ModuleDef;
    };
}
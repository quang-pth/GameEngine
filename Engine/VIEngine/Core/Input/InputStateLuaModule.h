#pragma once

#include"InputState.h"
#include"VIScript/LuaModule.h"

namespace VIEngine {
    class InputStateLuaModule {
    public:
        static LuaModuleDef<InputState> ModuleDef;
    };
}
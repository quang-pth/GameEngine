#include"InputStateLuaModule.h"
#include"Core/Application.h"
#include"Core/System/ScriptSystem.h"
#include"VIScript/LuaExecutor.h"
#include"KeyboardLuaModule.h"
#include"MouseInputLuaModule.h"

namespace VIEngine {
    const std::string NAME = "InputState";

    InputState* GetObject(lua_State* L) {
        return *reinterpret_cast<InputState**>(lua_touserdata(L, 1));
    }

    int lua_GetKeyboard(lua_State* L) {
        InputState* inputState = GetObject(L);
        static LuaExecutor* executor = Application::Get().GetSystem<ScriptSystem>().GetLuaExecutor();

        executor->PushValue(LuaUserData::Create(
            inputState->Keyboard,
            KeyboardLuaModule::ModuleDef.GetMetableName(),
            KeyboardLuaModule::ModuleDef.GetRegs(),
            KeyboardLuaModule::ModuleDef.GetAttributes()
        ));

        return 1;
    }

    int lua_GetMouseInput(lua_State* L) {
        InputState* inputState = GetObject(L);
        static LuaExecutor* executor = Application::Get().GetSystem<ScriptSystem>().GetLuaExecutor();

        executor->PushValue(LuaUserData::Create(
            inputState->Mouse,
            MouseInputLuaModule::ModuleDef.GetMetableName(),
            MouseInputLuaModule::ModuleDef.GetRegs(),
            MouseInputLuaModule::ModuleDef.GetAttributes()
        ));

        return 1;
    }

    LuaModuleDef<InputState> InputStateLuaModule::ModuleDef =
        LuaModuleDef<InputState>
    {
        NAME,
        { // Regs
            {"GetKeyboard", lua_GetKeyboard},
            {"GetMouse", lua_GetMouseInput},
            {NULL, NULL}
        },
        { // Attributes
        },
        [](lua_State* L) -> InputState* {
            VI_ASSERT(false && "Should not be called from lua side");
            return nullptr;
        },
        [](InputState* obj) -> void {
            VI_ASSERT(false && "Should not be called from lua side");
        }
    };
}
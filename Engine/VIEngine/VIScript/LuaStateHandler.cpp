#include"IStateHandler.h"

namespace VIEngine {
    LuaStateHandler::LuaStateHandler() {

    }

    LuaStateHandler::~LuaStateHandler() {

    }

    void LuaStateHandler::Handle(int32_t state, const std::string& message) {
        mMessage = message;

        switch (state)
        {
            case LUA_OK:
                mState = EScriptState::OK;
                break;
            case LUA_YIELD:
                mState = EScriptState::YIELD;
                break;
            case LUA_ERRRUN:
                mState = EScriptState::ERR_RUN;
                break;
            case LUA_ERRSYNTAX:
                mState = EScriptState::ERR_SYNTAX;
                break;
            case LUA_ERRMEM:
                mState = EScriptState::ERR_MEM;
                break;
            case LUA_ERRERR:
                mState = EScriptState::ERR_ERR;
                break;
            case LUA_ERRFILE:
                mState = EScriptState::ERR_FILE;
                break;
            default:
                // TODO: Log warnings for unknown state type
                mState = EScriptState::OK;
                break;
        }

        if (mState != EScriptState::OK) {
            std::cerr << mMessage.c_str() << std::endl;
            assert(false);
        }
    }
}
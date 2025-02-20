#pragma once

#include"Lua.hpp"

namespace VIEngine {
    enum class EScriptState {
        OK = 0,
        YIELD,
        ERR_RUN,
        ERR_SYNTAX,
        ERR_MEM,
        ERR_ERR,
        ERR_FILE
    };

    class IStateHandler {
        public:
            virtual ~IStateHandler() = default;
            virtual void Handle(int32_t state, const std::string& message) = 0;
            virtual EScriptState GetState() = 0;
            virtual std::string GetMessage() = 0;
    };

    class LuaStateHandler : public IStateHandler {
        public:
            LuaStateHandler();
            ~LuaStateHandler();
            virtual void Handle(int32_t state, const std::string& message) override;
            virtual EScriptState GetState() override { return mState; }
            virtual std::string GetMessage() override { return mMessage; }
        private:
            EScriptState mState;
            std::string mMessage;
    };
}
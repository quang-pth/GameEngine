#pragma once

#include"Lua.hpp"
#include"IStateHandler.h"
#include"LuaModule.h"

namespace VIEngine {
    class LuaExecutor {
        public:
            static const int VersionCode = 6;
        public:
            LuaExecutor(IStateHandler* handler);
            virtual ~LuaExecutor();
            // Load, compile file into a chunk and put onto Lua stack
            void ExecuteFromFile(const std::string& filepath);
            // Load, compile Lua raw source into a chunk and put onto Lua stack
            void ExecuteFromSource(const std::string& rawSource);

            LuaValue GetGlobal(const std::string& name);
            void SetGlobal(const std::string& name, const LuaValue& value);

            // Get value by its key from a table
            LuaValue GetValueFromTable(const std::string& tableName, const std::string& key);
            void SetTableValue(const std::string& tableName, const std::string& key, const LuaValue& value);

            // Gets value by its index from an array
            LuaValue GetValueFromTable(const std::string& tableName, int32_t index);
            void SetTableValue(const std::string& tableName, int32_t index, const LuaValue& value);

            void RegisterModule(LuaModule*);

            LuaValue GetRegistry(const LuaValue& key);
            void SetRegistry(const LuaValue& key, const LuaValue& value);

            template<typename... Args>
            LuaValue Invoke(const std::string& function, const Args&... args) {
                int type = lua_getglobal(mL, function.c_str());

                if (type != LUA_TFUNCTION) {
                    mStateHandler->Handle(LUA_ERRRUN, "Param is not a function type");
                    lua_pop(mL, 1);
                }

                for (auto param : std::initializer_list<LuaValue>{args...}) {
                    PushValue(param);
                }

                PCall(sizeof...(args), 1);
                return PopValue();
            }
            
            template<typename... Args>
            LuaValue InvokeTableFunction(const std::string& table, const std::string& function, bool passSelf, const Args&... args) {
                int type = lua_getglobal(mL, table.c_str());
                if (type != LUA_TTABLE) {
                    mStateHandler->Handle(LUA_ERRRUN, "Param is not a table type");
                    lua_pop(mL, 1);
                }

                type = lua_getfield(mL, -1, function.c_str());
                if (type != LUA_TFUNCTION) {
                    mStateHandler->Handle(LUA_ERRRUN, "Param is not a function type");
                    lua_pop(mL, 1);
                }

                if (passSelf) {
                    lua_getglobal(mL, table.c_str()); // Pass table itself as the first argument into the function
                }

                for (auto param : std::initializer_list<LuaValue>{args...}) {
                    PushValue(param);
                }

                PCall(sizeof...(args) + (int32_t)passSelf, 1);
                lua_pop(mL, 1); // Remove the table from the stack
                return PopValue();
            }

            template<typename... Args>
            std::vector<LuaValue> VInvoke(const std::string& function, const Args&... args) {
                int currentStackSize = lua_gettop(mL);

                int type = lua_getglobal(mL, function.c_str());
                if (type != LUA_TFUNCTION) {
                    mStateHandler->Handle(LUA_ERRRUN, "Param is not a function type");
                    lua_pop(mL, 1);
                }

                for (auto param : std::initializer_list<LuaValue>{args...}) {
                    PushValue(param);
                }

                if (PCall(sizeof...(args), LUA_MULTRET)) {
                    int nresults = lua_gettop(mL) - currentStackSize;
                    std::vector<LuaValue> values = PopValues(nresults);
                    return values;
                }

                return std::vector<LuaValue>();
            }

            template<typename... Args>
            std::vector<LuaValue> VInvokeTableFunction(const std::string& table, const std::string& function, bool passSelf, const Args&... args) {
                int currentStackSize = lua_gettop(mL);

                int type = lua_getglobal(mL, table.c_str());
                if (type != LUA_TTABLE) {
                    mStateHandler->Handle(LUA_ERRRUN, "Param is not a table type");
                    lua_pop(mL, 1);
                }

                type = lua_getfield(mL, -1, function.c_str());
                if (type != LUA_TFUNCTION) {
                    mStateHandler->Handle(LUA_ERRRUN, "Param is not a function type");
                    lua_pop(mL, 1);
                }

                if (passSelf) {
                    lua_getglobal(mL, table.c_str());
                }

                for (auto param : std::initializer_list<LuaValue>{args...}) {
                    PushValue(param);
                }

                std::vector<LuaValue> values;
                if (PCall(sizeof...(args) + (int32_t)passSelf, LUA_MULTRET)) {
                    int nresults = lua_gettop(mL) - currentStackSize - 1; // Minus one for not consider the table it self as a different in stack size
                    values = PopValues(nresults);
                }

                lua_pop(mL, 1); // Remove the table from the stack
                return values;
            }

            void PushValue(const LuaValue& value);
        private:
            // Execute file on top of the stack, then remove it
            bool PCall(int32_t nargs = 0, int32_t nresults = 0);
            std::string PopString();
            LuaValue GetValue(int32_t index);
            LuaValue PopValue();
            std::vector<LuaValue> PopValues(int nresults);
            void DumpStack();
        private:
            lua_State* const mL;
            IStateHandler* mStateHandler;
    };
}
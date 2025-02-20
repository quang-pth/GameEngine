#pragma once

#include"LuaModule.h"

namespace VIEngine {
    template<typename T>
    class LuaModuleExporter final : public LuaModule {
        public:
            LuaModuleExporter(const LuaModuleExporter&) = delete;
            ~LuaModuleExporter() = default;

            static LuaModuleExporter<T> Create(const LuaModuleDef<T>& moduleDef) {
                return LuaModuleExporter<T>(moduleDef);
            }

            static LuaModuleExporter<T>* Get(lua_State* L) {
                return reinterpret_cast<LuaModuleExporter<T>*>(lua_touserdata(L, lua_upvalueindex(1)));
            }

            const std::string &LuaName() const override 
            {
                return mModuleDef.GetModuleName(); 
            } 
            
            const std::vector<luaL_Reg> &Regs() const override 
            {
                return mRegs; 
            }

            virtual int32_t PushUpValues(lua_State* L) const {
                lua_pushlightuserdata(L, (void*)this);
                return 1;
            }

        private:
            LuaModuleExporter(const LuaModuleDef<T>& moduleDef) : mModuleDef(moduleDef) {}
            static int LuaDelete(lua_State* L) {
                // 1 is the index (in the stack call) of self argument passed by lua
                T* obj = *reinterpret_cast<T**>(lua_touserdata(L, 1));
                /*
                * Currently this not work, i don't know why
                * TODO: Fix later
                */
                // auto luaModuleDef = Get(L)->mModuleDef;
                // luaModuleDef.DeleteInstance(obj);
                delete obj;
                return 0;
            }

            static int LuaNew(lua_State *L) { 
                auto exporter = Get(L);
                auto luaModuleDef = exporter->mModuleDef;

                T* obj = luaModuleDef.CreateInstance(L);
                lua_settop(L, 0); // Reset the stack to avoid any side effect after create instance
                void** address = reinterpret_cast<void**>(lua_newuserdatauv(L, sizeof(obj), 0));
                *address = obj;
        
                int type = luaL_getmetatable(L, luaModuleDef.GetMetableName().c_str());
                if (type == LUA_TNIL) {
                    // Pop nil value 
                    lua_pop(L, 1);
                    // Create new metable table
                    luaL_newmetatable(L, luaModuleDef.GetMetableName().c_str());
                    // Copy itself and push on the stack
                    lua_pushvalue(L, -1);
                    // Set metable as metable for itself
                    lua_setfield(L, -2, "__index");
                    luaL_setfuncs(L, luaModuleDef.GetRegs().data(), 0);
                    // Register function for garbage collection
                    lua_pushlightuserdata(L, exporter); // Push exporter instance as an upvalue for LuaDelete function because it's not export as module like LuaNew
                    lua_pushcclosure(L, LuaDelete, 1);
                    lua_setfield(L, -2, "__gc");
                    // Register function for metatable
                }
                // Set metatable to userdata
                lua_setmetatable(L, 1);

                return 1;
            }
        private: 
            const std::string mName = "TODO"; 
            const std::vector<luaL_Reg> mRegs = { 
                {"Create", LuaNew}, 
                {NULL, NULL}
            };
            const LuaModuleDef<T> mModuleDef;
    };
}
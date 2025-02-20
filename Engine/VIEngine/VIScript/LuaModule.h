#pragma once

#include"Lua.hpp"

namespace VIEngine {
    class LuaModule {
        public:
            virtual ~LuaModule() = default;
            // Export C++ instance to lua as table name
            virtual const std::string& LuaName() const = 0;
            // Export C++ functions to lua
            virtual const std::vector<luaL_Reg>& Regs() const = 0;
            virtual int32_t PushUpValues(lua_State*) const = 0;
    };

    template<typename T>
    class LuaModuleDef {
        public:
            LuaModuleDef() = default;
            LuaModuleDef(const std::string& name, const std::vector<luaL_Reg>& regs, std::function<T* (lua_State*)> createFunction, std::function<void (T*)> deleteFunction) 
                : mModuleName(name), mRegs(regs), mCreateInstance(createFunction), mDeleteInstance(deleteFunction) {}
            const std::string& GetModuleName() const { return mModuleName; }
            const std::vector<luaL_Reg>& GetRegs() const { return mRegs; }
            T* CreateInstance(lua_State* L) { return mCreateInstance(L); }
            void DeleteInstance(T* obj) { mDeleteInstance(obj); }
            std::string GetMetableName() const { return std::string(mModuleName).append(".MetaTable"); }
        private:
            const std::string mModuleName;
            const std::vector<luaL_Reg> mRegs;
            const std::function<T* (lua_State*)> mCreateInstance;
            const std::function<void (T*)> mDeleteInstance;
    };
}
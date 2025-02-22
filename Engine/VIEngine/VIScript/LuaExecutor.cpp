#include"LuaExecutor.h"

namespace VIEngine {
    LuaExecutor::LuaExecutor(IStateHandler* handler) : mL(luaL_newstate()), mStateHandler(handler) {
        luaL_openlibs(mL);
        assert(mStateHandler != nullptr && "Invalid state handler is set");
    }

    LuaExecutor::~LuaExecutor() {
        lua_close(mL);
        delete mStateHandler;
    }

    void LuaExecutor::ExecuteFromFile(const std::string& filepath) {
        int32_t result = luaL_loadfile(mL, filepath.c_str()); 

        if (result != LUA_OK) {
            mStateHandler->Handle(result, PopString());
            lua_pop(mL, 1);
            return;
        }

        PCall();
    }

    void LuaExecutor::ExecuteFromSource(const std::string& rawSource) {
        int32_t result = luaL_loadstring(mL, rawSource.c_str()); 
        if (result != LUA_OK) {
            mStateHandler->Handle(result, PopString());
            lua_pop(mL, 1);
            return;
        }

        PCall();
    }

    LuaValue LuaExecutor::GetGlobal(const std::string& name) {
        lua_getglobal(mL, name.c_str());
        return PopValue();
    }

    void LuaExecutor::SetGlobal(const std::string& name, const LuaValue& value) {
        PushValue(value);
        lua_setglobal(mL, name.c_str());
    }

    LuaValue LuaExecutor::GetValueFromTable(const std::string& tableName, const std::string& key) {
        int type = lua_getglobal(mL, tableName.c_str()); // Push table onto the stack
        assert(type == LUA_TTABLE && "Invalid global table name");

        // Optimized version for access value by string as key
        lua_getfield(mL, -1, key.c_str());
        LuaValue value = PopValue();
        lua_pop(mL, 1);

        // General version
        {
            // lua_pushstring(mL, key.c_str()); // Push table key onto the stack
            // lua_gettable(mL, -2); // Push table (index -2) value (access by its key at index -1) onto the stack
            // LuaValue value = PopValue(); // Get table (index -2) value by its key (index -1)
            // lua_pop(mL, 1); // Remove the table from the stack
        }

        return value;
    }

    void LuaExecutor::SetTableValue(const std::string& tableName, const std::string& key, const LuaValue& value) {
        int type = lua_getglobal(mL, tableName.c_str()); // Push table onto the stack
        assert(type == LUA_TTABLE && "Invalid global table name");

        // Optimized version for set value by string as key
        PushValue(value);
        lua_setfield(mL, -2, key.c_str());
        lua_pop(mL, 1);

        // General version
        {
            // lua_pushstring(mL, key.c_str());
            // PushValue(value);
            // lua_settable(mL, -3); // Set table value for key then pop both of them
            // lua_pop(mL, 1); // Remove the table from the stack
        }
    }

    LuaValue LuaExecutor::GetValueFromTable(const std::string& tableName, int32_t index) {
        int type = lua_getglobal(mL, tableName.c_str()); // Push table onto the stack
        assert(type == LUA_TTABLE && "Invalid global table name");
        lua_geti(mL, -1, index); // Table now at index -1, retrieve the value at given index
        LuaValue value = PopValue(); // Get and Pop  the value at index that pushed onto the top of the stack
        lua_pop(mL, 1); // Remove the table
        return value;
    }

    void LuaExecutor::SetTableValue(const std::string& tableName, int32_t index, const LuaValue& value) {
        int type = lua_getglobal(mL, tableName.c_str()); // Push table onto the stack
        assert(type == LUA_TTABLE && "Invalid global table name");
        PushValue(value);
        lua_seti(mL, -2, index); // This function expects the value at the top of the stack, it also remove the value from the stack after executed
        lua_pop(mL, 1); // Remove the table
    }

    void LuaExecutor::RegisterModule(LuaModule* luaModule) {
        lua_createtable(mL, 0, luaModule->Regs().size());
        // lua_newtable(mL); also works if we need to create an empty table
        int32_t upvalues = luaModule->PushUpValues(mL);
        // Set the functions to the table at top of the stack, also the number of upvalues that it manages on its own context 
        luaL_setfuncs(mL, luaModule->Regs().data(), upvalues);
        lua_setglobal(mL, luaModule->LuaName().c_str());
    }

    LuaValue LuaExecutor::GetRegistry(const LuaValue& key) {
        PushValue(key);
        lua_gettable(mL, LUA_REGISTRYINDEX);
        return PopValue();
    }

    void LuaExecutor::SetRegistry(const LuaValue& key, const LuaValue& value) {
        PushValue(key);
        PushValue(value);
        lua_settable(mL, LUA_REGISTRYINDEX);
    }

    bool LuaExecutor::PCall(int32_t nargs, int32_t nresults) {
        // The 4th argument means there's no error function handler specified, so Lua will handle itself
        int32_t result = lua_pcall(mL, nargs, nresults, 0); 
        
        if (result != LUA_OK) {
            mStateHandler->Handle(result, PopString());
            lua_pop(mL, 1);
            return false;
        }

        return true;
    }

    std::string LuaExecutor::PopString() {
        return std::get<LuaString>(PopValue()).Value;
    }

    void LuaExecutor::PushValue(const LuaValue& value) {
        switch (GetLuaType(value))
        {
            case ELuaType::nil:
                lua_pushnil(mL);
                break;
            case ELuaType::boolean:
                lua_pushboolean(mL, std::get<LuaBoolean>(value).Value);
                break;
            case ELuaType::number:
                lua_pushnumber(mL, std::get<LuaNumber>(value).Value);
                break;
            case ELuaType::string:
                lua_pushstring(mL, std::get<LuaString>(value).Value.c_str());
                break;
            case ELuaType::function:
                assert(false && "Push function onto the stack is not supported");
                break;
            case ELuaType::table:
                assert(false && "Push table onto the stack is not supported");
                break;
            case ELuaType::lightUserData:
                lua_pushlightuserdata(mL, std::get<LuaLightUserData>(value).Value);
                break;
            case ELuaType::userData:
                {
                    LuaUserData userData = std::get<LuaUserData>(value);
                    void* data = userData.Value;
                    void** address = reinterpret_cast<void**>(lua_newuserdata(mL, sizeof(void*)));
                    *address = data;

                    int type = luaL_getmetatable(mL, userData.MetableName.c_str());
                    if (type == LUA_TNIL) {
                        // Pop nil value
                        lua_pop(mL, 1);
                        // Create new metable table
                        luaL_newmetatable(mL, userData.MetableName.c_str());

                        // Copy itself and push on the stack
                        lua_pushvalue(mL, -1);
                        // TODO: Create (getter/setter) for index attributes
                        // for (auto const &[key, value] : userData.Attributes) {
                        //     lua_pushstring(mL, key.c_str());
                        //     lua_pushcfunction(mL, value);
                        //     lua_settable(mL, -3);
                        // }

                        // Set metable as metable for itself
                        lua_setfield(mL, -2, "__index");
                        // // Register function for garbage collection
                        // lua_pushcfunction(mL, lua_Destination_Delete);
                        // lua_setfield(mL, -2, "__gc");
                        // Register function for metatable
                        luaL_setfuncs(mL, userData.Regs.data(), 0);
                    }
                    // Set metatable to userdata
                    lua_setmetatable(mL, -2);
                }
                break;
            default:
                assert(false && "Invalid lua value type");
                break;
        }
    }

    LuaValue LuaExecutor::GetValue(int32_t index) {
        switch (lua_type(mL, index))
        {
            case LUA_TNIL:
                return LuaNil::Create();
                break;
            case LUA_TBOOLEAN:
                return LuaBoolean::Create(lua_toboolean(mL, index) == 1);
                break;
            case LUA_TNUMBER:
                return LuaNumber::Create((float)lua_tonumber(mL, index));
                break;
            case LUA_TSTRING:
                return LuaString::Create(lua_tostring(mL, index));
                break;
            case LUA_TFUNCTION:
                return LuaFunction::Create();
                break;
            case LUA_TTABLE:
                return LuaTable::Create();
                break;
            case LUA_TLIGHTUSERDATA:
                return LuaLightUserData::Create(lua_touserdata(mL, index));
                break;
            default:
                return LuaNil::Create();
                break;
        }
    }

    LuaValue LuaExecutor::PopValue() {
        // 1st element on top of the stack is indexed by -1
        // 2nd element on top of the stack is indexed by -2
        // ...
        // 1st or bottom of the stack is indexed by 1
        // 2nd from the bottom of the stack is indexed by 2
        // ...
        // DUMP_LUA_STACK
        auto value = GetValue(-1);
        lua_pop(mL, 1);
        // DUMP_LUA_STACK
        return value;
    }

    std::vector<LuaValue> LuaExecutor::PopValues(int nresults) {
        std::vector<LuaValue> values;   

        // First value to be returned will be push first onto the stack, and so on
        // so we iterate backward the stack to get the return values in the correct order
        for (int i = nresults; i > 0; i--) {
            values.push_back(GetValue(-i));
        }
        lua_pop(mL, nresults);

        // for (int i = 0; i < nresults; i++) {
        //     values.push_back(GetValue(-1));
        //     // lua_settop(mL, lua_gettop(mL) - 1);
        //     // lua_remove(mL, -1);
        //     lua_pop(mL, 1);
        // }

        return values;
    }

    void LuaExecutor::DumpStack() {
        std::cout << "================\n";
        std::cout << "------STACK-----\n";
        std::cout << "================\n";
        int currentSize = lua_gettop(mL);

        for (int i = 1; i <= currentSize; i++) {
            std::cout << -i << ": " << GetLuaValueAsString(GetValue(-i)).c_str() << "\n";
        }
    }
}
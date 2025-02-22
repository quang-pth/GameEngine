#pragma once

#include"pch.h"

namespace VIEngine {
    enum class ELuaType {
        nil,
        boolean,
        number,
        string,
        function,
        table,
        lightUserData,
        userData
    };

    struct LuaNil final {
        public:
            const ELuaType Type = ELuaType::nil;
            const std::nullptr_t Value = nullptr;
            static LuaNil Create() { return LuaNil(); }
        private:
            LuaNil() = default;
    };
    
    struct LuaBoolean final {
        public:
            const ELuaType Type = ELuaType::boolean;
            const bool Value;
            static LuaBoolean Create(bool value) { return LuaBoolean(value); }
        private:
            LuaBoolean(bool value) : Value(value) {}
    };
    
    struct LuaNumber final {
        public:
            const ELuaType Type = ELuaType::number;
            const float Value;
            static LuaNumber Create(float value) { return LuaNumber(value); }
        private:
            LuaNumber(float value) : Value(value) {}
    };

    struct LuaString final {
        public:
            const ELuaType Type = ELuaType::string;
            const std::string Value;
            static LuaString Create(const std::string& value) { return LuaString(value); }
        private:
            LuaString(const std::string& value) : Value(value) {}
    };

    struct LuaFunction final {
        public:
            const ELuaType Type = ELuaType::function;
            const std::nullptr_t Value = nullptr;
            static LuaFunction Create() { return LuaFunction(); } 
        private:
            LuaFunction() : Value() {}
    };

    struct LuaTable final {
        public:
            const ELuaType Type = ELuaType::table;
            const std::nullptr_t Value = nullptr;
            static LuaTable Create() { return LuaTable(); }
        private:
            LuaTable() : Value() {}
    };

    struct LuaLightUserData final {
        public:
            const ELuaType Type = ELuaType::lightUserData;
            void* Value;
            static LuaLightUserData Create(void* value) { return LuaLightUserData(value); }
        private:
            LuaLightUserData(void* value) : Value(value) {}
    };

    using LuaIndexAttributes = std::unordered_map<std::string, lua_CFunction>;
    struct LuaUserData final {
        public:
            const ELuaType Type = ELuaType::userData;
            void* Value;
            std::string MetableName;
            std::vector<luaL_Reg> Regs;
            LuaIndexAttributes Attributes;
            static LuaUserData Create(void* value, const std::string& metaTableName, const std::vector<luaL_Reg>& regs, const LuaIndexAttributes& attributes) { return LuaUserData(value, metaTableName, regs, attributes); }
        private:
            LuaUserData(void* value, const std::string& metaTableName, const std::vector<luaL_Reg>& regs, const LuaIndexAttributes& attributes) : Value(value), MetableName(metaTableName), Regs(regs), Attributes(attributes) {}
    };

    using LuaValue = std::variant<LuaNil, LuaBoolean, LuaNumber, LuaString, LuaFunction, LuaTable, LuaLightUserData, LuaUserData>;

    inline ELuaType GetLuaType(const LuaValue& value) {
        return std::visit([](const auto& v) {
            return v.Type;
        }, value);
    }

    inline std::string GetLuaValueAsString(const LuaValue& value) {
        std::stringstream stream;
        
        switch (GetLuaType(value))
        {
            case ELuaType::nil:
                return "nil";
                break;
            case ELuaType::boolean:
                return std::get<LuaBoolean>(value).Value ? "true" : "false";
                break;
            case ELuaType::number:
                return std::to_string(std::get<LuaNumber>(value).Value);
                break;
            case ELuaType::string:
                return std::get<LuaString>(value).Value;
                break;
            case ELuaType::function:
                return "Function";
                break;
            case ELuaType::table:
                return "Table";
                break;
            case ELuaType::lightUserData:
                stream << std::hex << std::get<LuaLightUserData>(value).Value;
                return "LightUserData at address " + stream.str();
                break;
            case ELuaType::userData:
                stream << std::hex << std::get<LuaUserData>(value).Value;
                return "UserData at address " + stream.str();
                break;
            default:
                assert(false && "Invalid lua value");
                break;
        }
    }

    template<typename T>
    inline T GetLuaLightUserData(const LuaValue& value) {
        ELuaType type = GetLuaType(value);
        assert(type == ELuaType::lightUserData && "Invalid light user data");
        return reinterpret_cast<T>(std::get<LuaLightUserData>(value).Value);
    }

    template<typename T>
    inline T GetLuatUserData(const LuaValue& value) {
        ELuaType type = GetLuaType(value);
        assert(type == ELuaType::userData && "Invalid user data");
        return reinterpret_cast<T>(std::get<LuaUserData >(value).Value);
    }
}
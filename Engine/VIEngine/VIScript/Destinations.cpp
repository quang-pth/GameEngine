#include"Destinations.h"

#include"Lua.hpp"
#include"LuaExecutor.h"

namespace VIEngine {
    const std::string NAME("Destinations");
    const std::string META_TABLE("Destinations.MetaTable");

    Destinations::Destinations() : mWishList() {
        std::cout << "Destinations instance created: " << std::hex << this << std::endl;
    }

    Destinations::Destinations(const std::string& name) : mName(name), mWishList() {
        std::cout << "Destinations instance created: " << std::hex << this << std::endl;
    }

    Destinations::~Destinations() {
        std::cout << "Destinations instance destroyed: "  << std::hex << this << std::endl;
    }

    void Destinations::Wish(const std::vector<std::string>& places) {
        for (auto const& place : places) {
            mWishList[place] = false;
        }
    }

    void Destinations::Went(const std::vector<std::string>& places) {
        for (auto const& place : places) {
            mWishList[place] = true;
        }
    }

    std::vector<std::string> Destinations::ListVisited() const {
        std::vector<std::string> places;
        for (auto const& [place, visited] : mWishList) {
            if (visited) {
                places.push_back(place);
            }
        }
        return places;
    }

    std::vector<std::string> Destinations::ListUnvisited() const {
        std::vector<std::string> places;
        for (auto const& [place, visited] : mWishList) {
            if (!visited) {
                places.push_back(place);
            }
        }
        return places;
    }

    Destinations* GetObject(lua_State* L) {
        // Get the Destination instance as upvalue from the top of the stack (not-really the stack but something that similar)
        // Destinations* self = reinterpret_cast<Destinations*>(lua_touserdata(L, lua_upvalueindex(1)));
        // const char* name = reinterpret_cast<const char*>(lua_touserdata(L, lua_upvalueindex(2)));
        // Destinations* temp = reinterpret_cast<Destinations*>(lua_touserdata(L, lua_upvalueindex(3)));
        // temp = self;

        /**
         * We can change the value of upvalues it inside the context of a lua_cfunction
         * But we can't point it to a different address if it's a pointer 
        */

        // 1 is the index of the first argument in the function
        // which is "self" object passed by lua 
        luaL_checkudata(L, 1, META_TABLE.c_str());
        return *reinterpret_cast<Destinations**>(lua_touserdata(L, 1));
    }

    // lua_CFunction wrapper to export
    int lua_Destinations_Wish(lua_State* L) { 
        int32_t numArgs = lua_gettop(L);

        Destinations* destination = GetObject(L);
        std::vector<std::string> places;
        for (int32_t i = numArgs - 1; i > 0; i--) {
            int32_t type = lua_type(L, -i);
            assert(type == LUA_TSTRING && "Invalid argument detected");
            places.push_back(lua_tostring(L, -i));
        }

        destination->Wish(places);

        return 0;
    }

    int lua_Destinations_Went(lua_State* L) { 
        int32_t numArgs = lua_gettop(L);

        Destinations* destination = GetObject(L);
        std::vector<std::string> places;
        for (int32_t i = numArgs - 1; i > 0; i--) {
            int32_t type = lua_type(L, -i);
            assert(type == LUA_TSTRING && "Invalid argument dected");
            places.push_back(lua_tostring(L, -i));
        }

        destination->Went(places);

        return 0; 
    }
    
    int lua_Destinations_ListVisited(lua_State* L) { 
        Destinations* destination = GetObject(L);

        for (auto const& place : destination->ListVisited()) {
            lua_pushstring(L, place.c_str());
        }

        return destination->ListVisited().size(); 
    }
    
    int lua_Destinations_ListUnvisited(lua_State* L) { 
        Destinations* destination = GetObject(L);

        for (auto const& place : destination->ListUnvisited()) {
            lua_pushstring(L, place.c_str());
        }

        return destination->ListUnvisited().size(); 
    }

    LuaModuleDef<Destinations> DestinationsLuaModuleDef::ModuleDef = 
        LuaModuleDef<Destinations>{
            NAME,
            {
                {"Wish", lua_Destinations_Wish},
                {"Went", lua_Destinations_Went},
                {"ListVisited", lua_Destinations_ListVisited},
                {"ListUnvisited", lua_Destinations_ListUnvisited},
                {NULL, NULL}
            },
            [](lua_State* L) -> Destinations* {
                int nArgs = lua_gettop(L);
                if (!nArgs) {
                    return new Destinations();
                }
        
                int type = lua_type(L, 1);
                assert(type == LUA_TSTRING && "Invalid #1 argument type provided, it should be a string ");
                const char* name = lua_tostring(L, 1);
                lua_pop(L, 1);
                return new Destinations(name);
            },
            [](Destinations* obj) -> void {
                delete obj;
            }
        };
}
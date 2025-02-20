#pragma once

#include"pch.h"
#include"LuaModule.h"

namespace VIEngine {
    class Destinations {
        public:
            Destinations();
            Destinations(const std::string& name);
            ~Destinations();

            void Wish(const std::vector<std::string>& places);
            void Went(const std::vector<std::string>& places);
            std::vector<std::string> ListVisited() const;
            std::vector<std::string> ListUnvisited() const;
        private:
            std::map<std::string, bool> mWishList;
            std::string mName;
    };

    class DestinationsLuaModuleDef {
        public:
            static LuaModuleDef<Destinations> ModuleDef;
    };
}
#pragma once

#include<stdint.h>
#include<assert.h>
#include<memory>

#define DISALLOW_COPY_AND_ASSIGN(Classname) \
    protected: \
        Classname(const Classname&) = default;


#if ON_VI_MEMORY
    #if DYNAMIC_BUILD
        #ifdef _MSC_VER
            #define VI_MEM_API __declspec(dllexport)
        #else
            #define VI_MEM_API __attribute__((visibility("default")))
        #endif
    #else
        #define VI_MEM_API
    #endif
#else
    #if DYNAMIC_IMPORT
        #ifdef _MSC_VER
            #define VI_MEM_API __declspec(dllimport)
        #else
            #define VI_MEM_API
        #endif
    #else
        #define VI_MEM_API
    #endif
#endif
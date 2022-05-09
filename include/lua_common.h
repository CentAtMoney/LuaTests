// lua_common.h
#ifndef LUA_COMMON_H
#define LUA_COMMON_H

#ifdef __cplusplus

extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

#else

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#endif // __cplusplus

#endif // LUA_COMMON_H

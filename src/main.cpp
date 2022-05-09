// main.cpp

// #include "application.h"

#include <iostream>

#include "lua_common.h"


int main(int argc, char** argv)
{

    /*
    application::create_info application_create_info;
    application_create_info.window_create_info = {
        .title = "LuaTest",
        .width = 800,
        .height = 600,
    };


    application app(application_create_info);
    app.run();
    */


    lua_State* L = luaL_newstate();

	luaopen_base(L);
	luaopen_math(L);
	luaopen_package(L);
	luaopen_string(L);
	luaopen_table(L);

    int status = luaL_dofile(L, "../lua/test.lua");
    if(status != LUA_OK)
    {
        std::cerr << "dofile failed, code: " << status << std::endl;
    }

    if(!lua_checkstack(L, 3))
    {
        std::cerr << "stack full or oom\n"; 
    }

    int global_table_type = lua_getglobal(L, "global_table");

    if(global_table_type != LUA_TTABLE)
    {
        std::cerr << "expected table got not table\n";
    }

    int global_table_x_type = lua_getfield(L, lua_gettop(L), "x");
    int global_table_x = lua_tonumber(L, lua_gettop(L));
    lua_pop(L, 1);

    int global_table_y_type = lua_getfield(L, lua_gettop(L), "y");
    int global_table_y = lua_tonumber(L, lua_gettop(L));
    lua_pop(L, 1);

    lua_pop(L, 1);

    lua_close(L);


    std::cout << "global_table.x = " << global_table_x << "\nglobal_table.y = " << global_table_y << std::endl;

    return 0;

}
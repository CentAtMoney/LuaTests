#include <stdlib.h>
#include <stdio.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"


static int my_print(lua_State* L)
{
	printf("Hello, World!\n");
	return 0;
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <lua file>\n", argv[0]);
		exit(1);
	}

	lua_State* L = luaL_newstate();
	if(L == NULL)
	{
		printf("There was an error creating a new lua state\n");
		exit(1);
	}

	luaopen_base(L);
	luaopen_debug(L);
	luaopen_math(L);
	luaopen_package(L);
	luaopen_string(L);
	luaopen_table(L);
	

	luaL_checkstack(L, 1, NULL);
	lua_register(L, "my_print", my_print);


	if(luaL_loadfile(L, argv[1]) == LUA_OK)
	{
		luaL_dofile(L, argv[1]);
	}


	lua_close(L);

	exit(0);
}

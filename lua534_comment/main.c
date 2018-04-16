#include <stdio.h>
#include "lualib.h"
#include "lauxlib.h"

struct test_size
{
	short a;
	short c;
	int b;
};

int Lua_myyield(lua_State* L)
{
	lua_pushinteger(L, 345);
	int a = lua_gettop(L);
	lua_yield(L, 1);
	a = lua_gettop(L);
	return 0;
}

int Lua_myresume(lua_State* L)
{
	int a = lua_tointeger(L, 1);
	lua_pushinteger(L, 6);
	lua_pushinteger(L, 7);
	lua_pushinteger(L, 8);
	lua_resume(L, NULL, 3);
	return 0;
}

void test_coroutine(lua_State* L)
{
	lua_pushcfunction(L, Lua_myyield);
	lua_setglobal(L, "myyield");

	lua_pushcfunction(L, Lua_myresume);
	lua_setglobal(L, "myresume");

	lua_State* L1 = lua_newthread(L);
	lua_getglobal(L, "foo");
	lua_xmove(L, L1, 1);
	int nRet = lua_resume(L1, NULL, 0);
	if (nRet == LUA_YIELD)
	{
	}
	int a = lua_tointeger(L1, 1);
	int b = lua_tointeger(L1, -1);
	int top = lua_gettop(L1);
	//Lua_myresume(L1);
	lua_settop(L, 0);
	lua_pushinteger(L1, 6);
	lua_pushinteger(L1, 7);
	lua_pushinteger(L1, 8);
	lua_resume(L1, NULL, 3);
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_dofile(L, "..//script//main.lua"))
		fprintf(stderr, lua_tostring(L, -1));

	//for other test
	test_coroutine(L);

	lua_close(L);

	getchar();
	return 0;
}
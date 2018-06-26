#include "LuaHelperFunctions.h"
#include <iostream>
#include <string>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
	}

bool luah::loadScript ( lua_State* L, const std::string& filename )
	{
	if ( !(luaL_loadfile ( L, filename.c_str ( ) ) || lua_pcall ( L, 0, 0, 0 )) )
		{
		return true;
		}
	else
		{
		std::cout << "Failed to load " << filename << std::endl;
		std::cout << lua_tostring ( L, -1 ) << std::endl;
		lua_pop ( L, 1 ); // pop the error message from stack
		return false;
		}
	}

void luah::lua_gettostack ( lua_State* L, const std::string& variableName )
	{
	int level = 0;
	std::string var = "";
	for ( unsigned int i = 0; i < variableName.size ( ); i++ )
		{
		if ( variableName.at ( i ) == '.' )
			{
			if ( level == 0 )
				{
				lua_getglobal ( L, var.c_str ( ) );
				}
			else
				{
				lua_getfield ( L, -1, var.c_str ( ) );
				}

			if ( lua_isnil ( L, -1 ) )
				{
				std::cout << "Error, can't get " << variableName << std::endl;
				return;
				}
			else
				{
				var = "";
				++level;
				}
			}
		else
			{
			var += variableName.at ( i );
			}
		}
	if ( level == 0 )
		{
		lua_getglobal ( L, var.c_str ( ) );
		}
	else
		{
		lua_getfield ( L, -1, var.c_str ( ) );
		}

	if ( level == 0 ) { return; } // no need to remove anything

	int tableIndex = lua_gettop ( L ) - level;
	lua_replace ( L, tableIndex );
	lua_settop ( L, tableIndex );
	}

void luah::loadGetKeysFunction ( lua_State* L )
	{
	std::string code =
		R"(function getKeys(t)
        s = {}
        for k, v in pairs(t) do 
            table.insert(s, k)
            end 
        return s 
        end)";
	luaL_dostring ( L, code.c_str ( ) );
	}

std::vector<std::string> luah::getTableKeys ( lua_State* L, const std::string& name )
	{
	lua_getglobal ( L, "getKeys" ); // get function
	if ( lua_isnil ( L, -1 ) )
		{
		std::cout << "Get keys function is not loaded. Loading..." << std::endl;
		loadGetKeysFunction ( L );
		lua_getglobal ( L, "getKeys" );
		}

	lua_gettostack ( L, name );

	lua_pcall ( L, 1, 1, 0 ); // execute function. Got table on stack

	lua_pushnil ( L );

	std::vector<std::string> keys;

	while ( lua_next ( L, -2 ) )
		{ // get values one by one
		if ( lua_type ( L, -1 ) == LUA_TSTRING )
			{
			
			keys.push_back ( lua_tostring ( L, -1 ) );
			}
		
		lua_pop ( L, 1 );
		}

	lua_settop ( L, 0 ); // remove s table from stack 
	return keys;
	}



LuaScript::LuaScript ( const std::string& filename )
	{
	L = luaL_newstate ( );
	if ( luaL_loadfile ( L, filename.c_str ( ) ) || lua_pcall ( L, 0, 0, 0 ) )
		{
		std::cout << "Error: failed to load (" << filename << ")" << std::endl;
		L = 0;
		}

	if ( L ) luaL_openlibs ( L );
	}

LuaScript::~LuaScript ( )
	{
	//if ( L ) lua_close ( L );
	}

void LuaScript::printError ( const std::string& variableName, const std::string& reason )
	{
	std::cout << "Error: can't get [" << variableName << "]. " << reason << std::endl;
	}

std::vector<int> LuaScript::getIntVector ( const std::string& name )
	{
	std::vector<int> v;
	lua_gettostack ( name.c_str ( ) );
	if ( lua_isnil ( L, -1 ) )
		{ // array is not found
		return std::vector<int> ( );
		}
	lua_pushnil ( L );
	while ( lua_next ( L, -2 ) )
		{
		v.push_back ( (int) lua_tonumber ( L, -1 ) );
		lua_pop ( L, 1 );
		}
	clean ( );
	return v;
	}


std::vector<std::string> LuaScript::getStringVector ( const std::string& name )
	{
	std::vector<std::string> v;
	lua_gettostack ( name.c_str ( ) );
	if ( lua_isnil ( L, -1 ) )
		{ // array is not found
		return std::vector<std::string> ( );
		}
	lua_pushnil ( L );
	while ( lua_next ( L, -2 ) )
		{
		v.push_back ( lua_tostring ( L, -1 ) );
		lua_pop ( L, 1 );
		}
	clean ( );
	return v;
	}



std::vector<std::string> LuaScript::getTableKeys ( const std::string& name )
	{
	std::string code =
		"function getKeys(name) "
		"s = \"\""
		"for k, v in pairs(_G[name]) do "
		"    s = s..k..\",\" "
		"    end "
		"return s "
		"end"; // function for getting table keys
	luaL_loadstring ( L,
					  code.c_str ( ) ); // execute code
	lua_pcall ( L, 0, 0, 0 );
	lua_getglobal ( L, "getKeys" ); // get function
	lua_pushstring ( L, name.c_str ( ) );
	lua_pcall ( L, 1, 1, 0 ); // execute function
	std::string test = lua_tostring ( L, -1 );
	std::vector<std::string> strings;
	std::string temp = "";
	std::cout << "TEMP:" << test << std::endl;
	for ( unsigned int i = 0; i < test.size ( ); i++ )
		{
		if ( test.at ( i ) != ',' )
			{
			temp += test.at ( i );
			}
		else
			{
			strings.push_back ( temp );
			temp = "";
			}
		}
	clean ( );
	return strings;
	}
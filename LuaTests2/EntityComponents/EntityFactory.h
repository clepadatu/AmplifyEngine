#pragma once
#include "LuaHelperFunctions.h"
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"

#include <map>
#include <string>
#include <typeindex>
#include "Entity.h"
#include "GraphicsComponent.h"
#include "NpcComponent.h"
#include "Component.h"
#include <iostream>
Entity* loadEntity(lua_State* L, const std::string& nodeName, const std::string& type, const int UID, const int UID_MARK);
//Entity* loadMenuEntity(const std::string& nodeName, const std::string& type, const int UID, const int UID_MARK);
class EntityFactory{

public:
	
	////Pass-in Types:
	//// 0 - 
	//// 
	////
	////
	//static Entity* NewMenuEntity(const std::string& nodeName,std::string& type, const int UID, const int UID_MARK)
	//	{
	//	if ( type == "MainMenu" )
	//		{
	//		auto e = loadMenuEntity ("MainMenu", UID, UID_MARK );
	//		return e;
	//		}
	//	if ( type == "PauseMenu" )
	//		{
	//		auto e = loadMenuEntity ("PauseMenu", UID, UID_MARK );
	//		return e;
	//		}
	//	if ( type == "GameOver" )
	//		{
	//		auto e = loadMenuEntity ("GameOver", UID, UID_MARK );
	//		return e;
	//		}
	//	return NULL;
	//	}
	//
	static Entity* NewEntity(lua_State* L, const std::string& nodeName,const std::string& type, const int UID, const int UID_MARK)
	{
		auto e = loadEntity(L, nodeName, type, UID, UID_MARK);
		return e;
		/*if (type == "ghost")
		{
			auto e = loadEntity(L, "ghost",UID,UID_MARK);
			return e;
		}

		if (type == "SuperGhost")
		{
			auto e = loadEntity(L, "SuperGhost", UID, UID_MARK);
			return e;
		}

		if (type == "Player")
		{
			auto e = loadEntity(L, "Player", UID, UID_MARK);
			return e;
		}

		if ( type == "PlayerProjectile" )
		{
		    auto e = loadEntity ( L, "PlayerProjectile", UID, UID_MARK );
			return e;
		}

		if ( type == "Background" )
			{
			auto e = loadEntity ( L, "Background", UID, UID_MARK );
			return e;
			}

		if ( type.find ( "Level" ) != std::string::npos )
			{
			auto e = loadEntity ( L, type, UID, UID_MARK );
			return e;
			}*/
	/*	if ( type == "Level1" )
			{
			auto e = loadEntity ( L, "Level1", UID, UID_MARK );
			return e;
			}
		if ( type. )
			{
			auto e = loadEntity ( L, "Level2", UID, UID_MARK );
			return e;
			}*/
		
	}

	

};


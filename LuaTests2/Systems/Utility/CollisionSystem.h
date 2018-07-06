#pragma once

#include <map>
#include <string>
#include <typeindex>
#include <iostream>
#include <list>

#include "../RenderingSystem.h"
#include "../../EntityComponents/Entity.h"
#include "../../EntityComponents/MenuComponent.h"
#include "../../EntityComponents/LevelComponent.h"

#include "EntitySystem.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
	}

#include "../../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"

class CollisionSystem
	{
	public:

	CollisionSystem ( );
	~CollisionSystem ();

	void linkWithInterface(Window* windowInterface);

	public:
		Window* windowInterface;

		void DoCollision ( std::list<Entity*> &OBJ, std::list<Entity*> &PROJ ); // AABB - AABB collision
		void DoCollision ( std::list<Entity*> &OBJ, Entity* &Player ); // AABB - AABB collision
		GLboolean CheckCollision ( Entity *one, Entity *two );
	};

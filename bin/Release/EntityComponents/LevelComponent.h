#pragma once

#include <string>
#include "Component.h"

class LevelComponent : public Component
	{
	public:
		LevelComponent ( luabridge::LuaRef& componentTable );
		std::string getName ( ) const
			{
			return Name;
			}
		void printLevelData();
		bool Active=false;
		int ID;
	public:
		
		std::string Name;
		int Enemies;
		int Time;
		int ghosts;
		int ghost_health;
		int SuperGhost;
		int SuperGhost_health;
		int Bombs;
		int Bombs_health;
		int Bullets;
	};
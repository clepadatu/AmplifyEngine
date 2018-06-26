#pragma once

#include <map>
#include <string>
#include <typeindex>
#include <iostream>
#include <list>
#include "../../EntityComponents/Entity.h"


class LevelSystem
	{

	public:

		LevelSystem( );
		~LevelSystem ( );

		void addEntity ( Entity* e );
		std::list<Entity*> getEntities ( ) const { return EntityList; };

	private:
		std::list<Entity*> EntityList;
	};
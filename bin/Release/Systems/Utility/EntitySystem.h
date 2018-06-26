#pragma once

#include <map>
#include <string>
#include <typeindex>
#include <iostream>
#include <list>
#include "../../EntityComponents/Entity.h"


class EntitySystem {

public:

	EntitySystem();
	~EntitySystem();

	void addEntity(Entity* e);
	std::list<Entity*> getEntities() const{ return EntityList; };
	void Reset ();
		
private:
	std::list<Entity*> EntityList;
};
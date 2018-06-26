#include "EntitySystem.h"

EntitySystem::EntitySystem()
{

}

EntitySystem::~EntitySystem()
{
	for (auto& c : EntityList)
	{
		delete c;		
	}
}

void EntitySystem::addEntity(Entity* e)
{
	EntityList.emplace_back(e);
}

void EntitySystem::Reset ( )
	{
	
	for ( Entity* ptr : EntityList ) delete ptr;
	EntityList.clear ( );

	}
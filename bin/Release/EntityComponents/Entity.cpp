#include "Entity.h"
#include "Component.h"
Entity::Entity(const int UID, const int UID_MARK)
{
	this->UID = UID + 100 * UID_MARK;
}
Entity::~Entity ( )
	{
	for ( auto& c : components )
		{
		delete c.second;
		}
	}

void Entity::addComponent ( std::type_index type, Component* c )
	{
	components [type] = c;
	}



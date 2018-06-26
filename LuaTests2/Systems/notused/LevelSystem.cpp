#include "LevelSystem.h"

LevelSystem::LevelSystem ( )
	{

	}

LevelSystem::~LevelSystem ( )
	{
	for ( auto& c : EntityList )
		{
		delete c;
		}
	}

void LevelSystem::addEntity ( Entity* e )
	{
	EntityList.emplace_back ( e );
	}
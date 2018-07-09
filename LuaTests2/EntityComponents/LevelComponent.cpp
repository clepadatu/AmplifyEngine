#include "LevelComponent.h"
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"
#include <iostream>

LevelComponent::LevelComponent ( luabridge::LuaRef& lcTable )
	{
	//MISSING ERROR CHECKS

	using namespace luabridge;
	auto IDRef = lcTable ["ID"];
	ID = IDRef.cast<int> ( );
	auto NameRef= lcTable ["Name"];
	Name = NameRef.cast<std::string> ( );

	auto TimeRef= lcTable ["Time"];
	Time = TimeRef.cast<int> ( );


	}

void LevelComponent::printLevelData()
{
	std::cout << "ID="<< ID<< std::endl;
	std::cout << "Name=" << Name << std::endl;
	std::cout << "Enemies=" << Enemies << std::endl;
	std::cout << "Time=" << Time << std::endl;
	std::cout << "Ghosts=" << ghosts << std::endl;
	std::cout << "Ghosts health=" << ghost_health << std::endl;
	std::cout << "SuperGhosts=" << SuperGhost << std::endl;
	std::cout << "SuperGhosts health=" << SuperGhost_health << std::endl;
	std::cout << "Active=" << Active << std::endl;
	std::cout << "Bullets=" << Bullets<< std::endl;
}
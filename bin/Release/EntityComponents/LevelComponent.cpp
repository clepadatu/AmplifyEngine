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
	auto EnemiesRef = lcTable ["Enemies"];
	Enemies = EnemiesRef.cast<int> ( );
	auto TimeRef= lcTable ["Time"];
	Time = TimeRef.cast<int> ( );
	auto GhostRef = lcTable ["ghost"];
	ghosts = GhostRef.cast<int> ( );
	auto GhostHRef= lcTable ["ghost_health"];
	ghost_health = GhostHRef.cast<int> ( );
	auto SuperGhostRef= lcTable ["SuperGhost"];
	SuperGhost = SuperGhostRef.cast<int> ( );
	auto SuperGhostHRef = lcTable ["SuperGhost_health"];
	SuperGhost_health = SuperGhostHRef.cast<int> ( );
	
	auto BulletsRef = lcTable ["Bullets"];
	Bullets = BulletsRef.cast<int> ( );

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
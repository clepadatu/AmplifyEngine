#pragma once

#include <map>
#include <string>
#include <typeindex>
#include <iostream>
#include <list>

#include "../EntityComponents\Entity.h"
#include "../EntityComponents\EntityFactory.h"
#include "../EntityComponents\NpcComponent.h"
#include "../EntityComponents\MenuComponent.h"
#include "../EntityComponents\TextComponent.h"
#include "../EntityComponents\LevelComponent.h"
#include "../EntityComponents\GraphicsComponent.h"

#include "SceneManager.h"
#include "GameLoopSystem.h"
#include "RenderingSystem.h"
#include "Utility\EntitySystem.h"
#include "Utility\CollisionSystem.h"

#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"




class MainSystem {

public:

	MainSystem();
	~MainSystem();


	int reqid;

private:
	RenderingSystem* RSYS; //Rendering System
	GameLoopSystem* GLSYS;
	InputSystem* ISYS;
	SceneManager* Curtain;	
	CollisionSystem* Collide;
};
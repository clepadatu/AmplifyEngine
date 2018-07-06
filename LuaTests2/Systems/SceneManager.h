#pragma once
#include <string>
#include <map>
#include <string>
#include <typeindex>
#include <iostream>
#include <list>
#include "../EntityComponents/Entity.h"
#include "../EntityComponents/EntityFactory.h"
#include "../EntityComponents/GraphicsComponent.h"
#include "../EntityComponents/TextComponent.h"
#include "../EntityComponents/MenuComponent.h"
#include "../EntityComponents/LevelComponent.h"
#include "../Extras/window/window.h"
#include "Utility\EntitySystem.h"
#include "SceneManager.h"
#include "GameLoopSystem.h"
#include "RenderingSystem.h"
#include "Utility\EntitySystem.h"
#include "Utility\CollisionSystem.h"

class SceneManager
	{
	public:
		//Keep a list of menus,levels,enemies and pass it on to the Renderer to display on screen
		SceneManager();
		~SceneManager();


		void linkAllInterfaces(RenderingSystem* Renderer, InputSystem* InputManager, CollisionSystem* Collisions, GameLoopSystem* GameLoop);
		void basicInitialization (int& code );
		// Read LVL and UI Data
		void readFramework();
		// Load LVL OBJ data - lvl 1 default loading
		void preloadLevelEntities ( );
		// Precision LVL loading
		void loadLevelEntities(int ID);

	/* NOT NEEDED ATM	void cacheData ( int typeID );*/



		void triggerNewLevel(int ID);

		void printLoadedTemplate ();

		std::list<Entity*> getUI ();
		std::list<Entity*> getLVL ();
		std::list<Entity*> getOBJ ();
		std::list<Entity*> getAmmo ();
	private:
		EntitySystem* UI;
		EntitySystem* LVL;
		EntitySystem* OBJ;
		EntitySystem* ammo;

		RenderingSystem* Renderer;
		InputSystem* InputManager;
		CollisionSystem* Collisions;
		GameLoopSystem* GameLoop;
		Window* windowInterface;


		std::list<Entity*> menuList;
		std::list<Entity*> levelList;
		std::list<Entity*> objectList;
		std::list<Entity*> ammoList;
	};
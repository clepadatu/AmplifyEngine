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

		// Provide hooks to Renderer, InputManager, Collisions, GameLoop
		void linkAllInterfaces(RenderingSystem* Renderer, InputSystem* InputManager, CollisionSystem* Collisions, GameLoopSystem* GameLoop);
		// Load basic resources and distribute them to all other systems
		void basicInitialization (int& code );
		// Read LVL and UI Data
		void readFramework();

		void readGameSettings ();
		void readLevelData ();

		void readUIData ();
		void readUIMenus ();
		void readUIBackgrounds ();
		// Load LVL OBJ data - lvl 1 default loading
		void preloadLevelEntities ( );
		// Precision LVL loading
		void loadLevelEntities(int ID);

	/* NOT NEEDED ATM	void cacheData ( int typeID );*/

		void setScene();


		void triggerNewLevel(int ID);

		void printLoadedTemplate ();

		std::list<Entity*> getUI ();
		std::list<Entity*> getLVL ();
		std::list<Entity*> getOBJ ();
		std::list<Entity*> getAmmo ();
	private:
		RenderingSystem* Renderer;
		InputSystem* InputManager;
		CollisionSystem* Collisions;
		GameLoopSystem* GameLoop;
		Window* windowInterface;

		EntitySystem* UI;
		EntitySystem* LVL;
		EntitySystem* OBJ;
		EntitySystem* ammo;	

		std::list<Entity*> menuList;
		std::list<Entity*> levelList;
		std::list<Entity*> objectList;
		std::list<Entity*> ammoList;

		int numberOfLevels;
		int numberOfMenus;
		int numberOfBackgrounds;
		struct Enemy
			{
			Entity* enemy;
			std::list<Entity*> rounds;
			};

		struct Scene
			{
			Entity* ePlayer;
			std::list<Entity*> ePlayerAmmo;
			std::list<Entity*> eUserInterface;
			std::list<Entity*> eLevel;
			std::list<Enemy> eEnemies;
			void temp();
			};

		Scene AmplifyScene;

	};
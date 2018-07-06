#pragma once

#include <map>
#include <string>
#include <typeindex>
#include <iostream>
#include <list>

#include "RenderingSystem.h"
#include "../EntityComponents/Entity.h"
#include "../EntityComponents/MenuComponent.h"
#include "../EntityComponents/LevelComponent.h"
#include "Utility\CollisionSystem.h"
#include "Utility/EntitySystem.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
	}

#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"
class SceneManager;
class InputSystem
	{
	
	public:
		InputSystem();
		~InputSystem ();

		void linkWithInterface(RenderingSystem* Renderer, CollisionSystem* Collisions, SceneManager* StageManager);

		void setMenus(std::list<Entity*> Entities, std::string type); //Set Initial List of Menus
		void setLevels(std::list<Entity*> Entities, std::string type); //Set Initial List of Levels
		void setLevelEntities(std::list<Entity*> Entities, std::string type); //Set Initial List of Entities, or reload different Entities
		void setAmmo ( std::list<Entity*> Entities, std::string type );

		void setActiveMenu(); //Get(set ActiveMenu) Active Menu Pointer
		void setActiveMenu(int UID); //Activate Menu - used for travelling
		int getActiveMenu(); //Get Active Menu - return Menu UID

		void setActiveLevel (); //Get(set ActiveLevel) Active Level Pointer
		void setActiveLevel(int UID); //Activate Level - used for travelling
		int getActiveLevel(); //Get Active Level - return Level UID
		
		void deactivateMenu ( Entity* menu ); //Deactive an activated menu
		void deactivateLevel ( Entity* level ); //Deactive an activated level


		void setActiveOption (); //Set Active options - facilitate Menu option switching

		void getInput();

		void processInput(bool whiletrue); //General Input processing
		void processMenuInput(); //Menu Input handler
		void processGameplayInput(); //Gameplay Input handler

		void processMenuSelection();

		void pollMenuKeys();		
		void pollGameplayKeys();


		void resetInput ();


		bool keyDPressed ();
		bool keyUpPressed ();
		bool keyDownPressed ();
		bool keyRightPressed ();
		bool keyLeftPressed ( );
		bool keyConfirmPressed();
		bool keyEscapePressed ();
		bool keySpacePressed ();

		bool getGameState();
		void closeGame();
		
		void detectPlayer ();
		void processPlayerInput ( );

		void ActivateProjectile ();
		void UpdateProjectiles ();
		void DoCollisions ();
		bool countdown ();
		void ResetOBJs ();

		void loadLevelEntities(int ID);

		std::list<Entity*> returnEntityList();

		bool game_running;
		std::string game_status;
		int req_id;
	private:
		RenderingSystem* Renderer;
		Window* windowInterface;
		CollisionSystem* Collisions;
		SceneManager* StageManager;

		EntitySystem* ESYS;

		std::list<Entity*> MenuList;
		std::list<Entity*> LevelList;
		std::list<Entity*> EntityList;
		std::list<Entity*> AmmoList;

		Entity* ActiveMenu;
		Entity* ActiveLevel;
		Entity* Player;

		std::string inputTypeReq; //

		//==Menu STory
		// EntityList holds 2 menus
		//	Each Menu has a title
		//	Each Menu has options
		//	Each Menu has actions associated with options
		//	
		int delay;		
		int menuDirection;
		int xAxis;
		int yAxis;
		double mouse_x = 0;
		double mouse_y = 0;
		bool launched = false;
		
		bool CD_status=false;
		double CD_Start;
		double CD_delay = 0.175;
	};
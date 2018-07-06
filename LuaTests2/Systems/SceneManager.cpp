#include "SceneManager.h"

SceneManager::~SceneManager(){}

SceneManager::SceneManager()
{
	UI = new EntitySystem();		//Menu System
	LVL = new EntitySystem();     //Level System
	OBJ = new EntitySystem();     //Object System
	ammo = new EntitySystem ();

}

void SceneManager::basicInitialization ( int& code )
	{

	readFramework ( );
	menuList = UI->getEntities ( ); //List of menus
	levelList = LVL->getEntities ( ); //List of levels
	preloadLevelEntities ( );
	objectList = OBJ->getEntities ( ); //List of objects
	ammoList = ammo->getEntities ( );

	printLoadedTemplate ( );
	code = 0;
	}

void SceneManager::linkAllInterfaces(RenderingSystem* Renderer, InputSystem* InputManager, CollisionSystem* Collisions, GameLoopSystem* GameLoop)
{
	this->Renderer = Renderer;
	this->InputManager = InputManager;
	this->Collisions = Collisions;
	this->GameLoop = GameLoop;
	windowInterface = this->Renderer->getWindow();
}

void SceneManager::triggerNewLevel ( int ID )
	{
	OBJ->Reset ( );
	loadLevelEntities ( ID );
	objectList = OBJ->getEntities ( );
	}


































//void SceneManager::cacheData ( int typeID )
//	{
//	switch ( typeID )
//		{
//
//		    //NOT NEEDED
//			case 0://UI
//				UI->Reset ( );
//				menuList = UI->getEntities ( );
//				break;
//			case 1://LVL
//				LVL->Reset ( );
//				levelList = LVL->getEntities ( );
//				break;
//
//			//ONLY ONE NEEEDED
//
//			case 2://OBJ
//				OBJ->Reset ( );
//				objectList = OBJ->getEntities ( );
//				break;
//
//		}
//	}




std::list<Entity*> SceneManager::getUI ()
	{
	return menuList;
	}
std::list<Entity*> SceneManager::getLVL ( )
	{
	return levelList;
	}
std::list<Entity*> SceneManager::getOBJ ( )
	{
	return objectList;
	}
std::list<Entity*> SceneManager::getAmmo ()
	{
	return ammoList;
	}













void SceneManager::readFramework ( )
	{

	//initialize LUA
	using namespace luabridge;
	lua_State* L = luaL_newstate ( );
	luaL_openlibs ( L );

	//Load LUA Level Data
	luah::loadScript ( L, "Scripts/levels/levels.lua" );
	luah::loadGetKeysFunction ( L );

	LVL->addEntity ( EntityFactory::NewEntity ( L, "Level1", 1, 9 ) );
	LVL->addEntity ( EntityFactory::NewEntity ( L, "Level2", 2, 9 ) );

	UI->addEntity ( EntityFactory::NewMenuEntity ( (std::string)"MainMenu", 10, 10 ) );
	UI->addEntity ( EntityFactory::NewMenuEntity ( (std::string)"PauseMenu", 19, 10 ) );
	UI->addEntity ( EntityFactory::NewMenuEntity ( (std::string)"GameOver", 29, 10 ) );

	}

void SceneManager::preloadLevelEntities ( )
	{

	std::cout << "Loading new level..." << std::endl;
	int tGhosts;
	int tSGhosts;
	int bullet_Count;
	std::list<Entity*>::iterator i = levelList.begin ( );
	while ( i != levelList.end ( ) )
		{
		if ( (*i)->get<LevelComponent> ( )->ID == 1 )
			{
			auto temp = (*i)->get<LevelComponent> ( );
			tGhosts = temp->ghosts;
			tSGhosts = temp->SuperGhost;
			bullet_Count = temp->Bullets;
			int tGhosts_hp = temp->ghost_health;
			int tSGhosts_hp = temp->SuperGhost_health;
			(*i)->get<LevelComponent> ( )->Active = true;

			}
		++i;
		}
	using namespace luabridge;
	lua_State* L = luaL_newstate ( );
	luaL_openlibs ( L );
	////Load LUA Entity Data
	luah::loadScript ( L, "Scripts/Levels/L1/ghost.lua" );
	luah::loadGetKeysFunction ( L );

	////Insert Entity Data
	OBJ->addEntity ( EntityFactory::NewEntity ( L, "Background", 100, 100 ) );
	for ( int i = 0; i < tGhosts; i++ )
		OBJ->addEntity ( EntityFactory::NewEntity ( L, "ghost", i, 1 ) );

	for ( int i = 0; i < tSGhosts; i++ )
		OBJ->addEntity ( EntityFactory::NewEntity ( L, "SuperGhost", i, 1 ) );

	OBJ->addEntity ( EntityFactory::NewEntity ( L, "Player", 100, 100 ) );

	for ( int i = 0; i < bullet_Count; i++ )
		ammo->addEntity ( EntityFactory::NewEntity ( L, "PlayerProjectile", 100, 101 ) );

	}



void SceneManager::loadLevelEntities ( int ID )
	{

	std::cout << "Loading new level..." << std::endl;
	int tGhosts;
	int tSGhosts;
	std::list<Entity*>::iterator i = levelList.begin ( );
	while ( i != levelList.end ( ) )
		{
		if ( (*i)->get<LevelComponent> ( )->ID == ID )
			{
			auto temp = (*i)->get<LevelComponent> ( );
			tGhosts = temp->ghosts;
			tSGhosts = temp->SuperGhost;

			int tGhosts_hp = temp->ghost_health;
			int tSGhosts_hp = temp->SuperGhost_health;
			(*i)->get<LevelComponent> ( )->Active = true;

			}
		++i;
		}
	using namespace luabridge;
	lua_State* L = luaL_newstate ( );
	luaL_openlibs ( L );
	////Load LUA Entity Data
	luah::loadScript ( L, "Scripts/Levels/L1/ghost.lua" );
	luah::loadGetKeysFunction ( L );

	////Insert Entity Data
	OBJ->addEntity ( EntityFactory::NewEntity ( L, "Background", 100, 100 ) );
	for ( int i = 0; i < tGhosts; i++ )
		OBJ->addEntity ( EntityFactory::NewEntity ( L, "ghost", i, 1 ) );
	for ( int i = 0; i < tSGhosts; i++ )
		OBJ->addEntity ( EntityFactory::NewEntity ( L, "SuperGhost", i, 1 ) );
	OBJ->addEntity ( EntityFactory::NewEntity ( L, "Player", 100, 100 ) );

	}

void SceneManager::printLoadedTemplate ( )
	{
	std::cout << "******" << std::endl;
	std::cout << "Loaded Menus List:" << std::endl;
	std::list<Entity*>::iterator i = menuList.begin ( );
	while ( i != menuList.end ( ) )
		{
		std::cout << (*i)->getType ( ) << std::endl;
		std::cout << (*i)->get<MenuComponent> ( )->getName ( ) << " - Active:" << (*i)->get<MenuComponent> ( )->Active << std::endl;
		std::cout << "******" << std::endl;
		std::cout << "Menu Options List:" << std::endl;
		(*i)->get<MenuComponent> ( )->printOptions ( );
		++i;
		std::cout << "******" << std::endl;
		}
	std::cout << "******" << std::endl;


	std::cout << "Loaded Levels List:" << std::endl;
	std::list<Entity*>::iterator k = levelList.begin ( );
	while ( k != levelList.end ( ) )
		{
		std::cout << (*k)->getType ( ) << std::endl;
		std::cout << (*k)->get<LevelComponent> ( )->getName ( ) << std::endl;
		(*k)->get<LevelComponent> ( )->printLevelData ( );
		++k;
		}
	std::cout << "******" << std::endl;

	std::cout << "Loaded Entities List:" << std::endl;
	std::list<Entity*>::iterator j = objectList.begin ( );
	while ( j != objectList.end ( ) )
		{
		std::cout << (*j)->getType ( ) << std::endl;
		//std::cout << (*j)->get<LevelComponent> ( )->getName ( ) << std::endl;
		++j;
		}
	std::cout << "******" << std::endl;
	}
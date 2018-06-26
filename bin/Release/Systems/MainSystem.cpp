#include "MainSystem.h"



MainSystem::MainSystem()
{

RSYS = new RenderingSystem ( );
Collide = new CollisionSystem ( RSYS );
Curtain = new SceneManager ();
ISYS = new InputSystem ( RSYS,Collide,Curtain);
RSYS->setUI ( Curtain->getUI());
RSYS->setOBJ ( Curtain->getOBJ ( ) );
RSYS->setAmmo ( Curtain->getAmmo () );
RSYS->enableUIOnly ();
ISYS->setLevelEntities ( Curtain->getOBJ ( ), "Gameplay" );
ISYS->setAmmo ( Curtain->getAmmo (),"" );
ISYS->setMenus(Curtain->getUI(), "UI");
ISYS->setLevels(Curtain->getLVL(), "UI");

GLSYS = new GameLoopSystem ( RSYS,ISYS );
GLSYS->DoMainLoop ();
//do reset object and add closed state or reloading stuff

reqid = ISYS->req_id;
if (ISYS->game_status != "Shutdown")
	{
	//RSYS = new RenderingSystem(); //Rendering System
	/*ESYS = new EntitySystem();
	loadLevelEntities(reqid);*/
	//RSYS->setEntities(Curtain->getOBJ(), "OBJ");
	ISYS->setMenus(Curtain->getUI(), "UI");
	ISYS->setLevels(Curtain->getLVL(), "");	
	ISYS->setLevelEntities ( Curtain->getOBJ ( ), "Gameplay" );
	RSYS->setUI ( Curtain->getUI () );
	RSYS->setOBJ ( Curtain->getOBJ () );
	RSYS->setAmmo ( Curtain->getAmmo () );
	RSYS->enableOBJOnly ();
	ISYS->setAmmo ( Curtain->getAmmo ( ),"" );
	ISYS->game_running = true;
	GLSYS->DoMainLoop();
	}

std::cout << "Time to go outside and play..." << std::endl;

};


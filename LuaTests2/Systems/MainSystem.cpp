#include "MainSystem.h"



MainSystem::MainSystem()
{
doingInception = true;
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

// do and set node movement and add Rendering System Jobs



// The Inception Loop - Halt Screen to current state display, and reload/release resources
// examples: - configure menu trees into Game Regions. Game Regions design.
//           - resource cleanup optimized to minimum operations
//           - idle/transition screen animation, preseeded with time duration analysis
//           - digital media injector and player
//           -


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
	//GLSYS->DoMainLoop();

	}

std::cout << "Time to go outside and play..." << std::endl;

};

void MainSystem::Inception ()
	{
	std::cout << "Starting engine..." << std::endl;
	while ( doingInception )
		{
		GLSYS->DoMainLoop ( );


//		RSYS->RunDefault ( );
		}
	}

void MainSystem::switchOffGLSYS ()
	{
	ISYS->game_running = false;
	}

void MainSystem::switchOnGLSYS ( )
	{
	ISYS->game_running = true;
	}
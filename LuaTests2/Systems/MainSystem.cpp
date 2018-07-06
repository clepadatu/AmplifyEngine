#include "MainSystem.h"



MainSystem::MainSystem()
{
std::cout << "Loading..." << std::endl;

doingInception = true;
errorCode = -1;
//Renderer = new RenderingSystem ( );
//Collisions = new CollisionSystem ( Renderer );
//InputManager = new InputSystem ( Renderer, Collisions, StageManager );
//StageManager = new SceneManager ( );//Knowledge of all systems; linker in Systems Initializer
//GameLoop = new GameLoopSystem ( Renderer, InputManager );


Renderer = new RenderingSystem();
Collisions = new CollisionSystem();
InputManager = new InputSystem();//revamp with input inverter grab from Window
StageManager = new SceneManager();//Knowledge of all systems; linker in Systems Initializer
GameLoop = new GameLoopSystem();
};

void MainSystem::fireUpTheEngine ()
	{
	std::cout << "Loading engine resources..." << std::endl;
	
	//Setup interfaces between systems
	Collisions->linkWithInterface(Renderer->getWindow());
	InputManager->linkWithInterface(Renderer, Collisions, StageManager);
	GameLoop->linkWithInterface(Renderer, InputManager);
	StageManager->linkAllInterfaces(Renderer, InputManager, Collisions, GameLoop);

	StageManager->basicInitialization (errorCode);


	std::cout << "Error=" << errorCode << std::endl;
	Renderer->setUI ( StageManager->getUI ( ) );
	Renderer->setOBJ ( StageManager->getOBJ ( ) );
	Renderer->setAmmo ( StageManager->getAmmo ( ) );
	Renderer->enableUIOnly ( );
	InputManager->setLevelEntities ( StageManager->getOBJ ( ), "Gameplay" );
	InputManager->setAmmo ( StageManager->getAmmo ( ), "" );
	InputManager->setMenus ( StageManager->getUI ( ), "UI" );
	InputManager->setLevels ( StageManager->getLVL ( ), "UI" );

	}

void MainSystem::Inception ()
	{
	std::cout << "Starting engine..." << std::endl;
	while ( doingInception )
		{
		GameLoop->DoMainLoop ( );

		
		Renderer->renderDefault ( );
		}
	}

void MainSystem::switchOffGLSYS ()
	{
	InputManager->game_running = false;
	}

void MainSystem::switchOnGLSYS ( )
	{
	InputManager->game_running = true;
	}
#include "MainSystem.h"



MainSystem::MainSystem()
{
std::cout << "Initializing systems..." << std::endl;

doingInception = true;
errorCode = -1;

Renderer = new RenderingSystem();
Collisions = new CollisionSystem();
InputManager = new InputSystem();//revamp with input inverter grab from Window
StageManager = new SceneManager();//Knowledge of all systems; linker in Systems Initializer
GameLoop = new GameLoopSystem();
};

void MainSystem::fireUpTheEngine ()
	{
	std::cout << "Loading engine resources..." << std::endl;
	
	//Setup interfaces between systems and initialize resources
	StageManager->linkAllInterfaces(Renderer, InputManager, Collisions, GameLoop);
	StageManager->basicInitialization (errorCode);

	if ( errorCode != 0 )
		std::cout << "Error=" << errorCode << std::endl;
	else
		std::cout << "All resources loaded successfuly." << std::endl;
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

void MainSystem::switchOffGameLoop ( )
	{
	InputManager->game_running = false;
	}

void MainSystem::switchOnGameLoop ( )
	{
	InputManager->game_running = true;
	}
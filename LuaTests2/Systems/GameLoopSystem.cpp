#include "GameLoopSystem.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
	}
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"


GameLoopSystem::GameLoopSystem ()
	{
	
	
	};

void GameLoopSystem::linkWithInterface(RenderingSystem* Renderer, InputSystem* InputManager)
{
	this->Renderer= Renderer;
	windowInterface = this->Renderer->getWindow();
	this->InputManager = InputManager;
}
void GameLoopSystem::DoMainLoop ()
	{
	
	while (InputManager->getGameState())
		{
		//game_active = InputManager->getGameState();
		//game_state = InputManager->game_state;
		current = clock ( );
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		getInput ( );
		//not ideal; input should be registered in process input;input should be processed in updateGameState()
		if ( Renderer->entityType == "UI" || Renderer->entityType == "UI+OBJ" )
		{

			while (lag >= 17)
				updateGameState();
		}
		else
		{
			while (lag >= 10)
				updateGameState();
		}
		
		renderScreen ( );

		}
	InputManager->game_running = false; //move this to getInput();
	}

void GameLoopSystem::getInput ()
	{
	windowInterface->clear ( );
	InputManager->getInput();
	}

void GameLoopSystem::updateGameState ( )
	{
	/*if (game_state == "Reload")
		Reload();*/
	
	InputManager->processInput();	
	lag -= 10;
	
	

	}

void GameLoopSystem::renderScreen ()
	{
	if ( InputManager->getGameState () == false )
		Renderer->goodbye = true;
	Renderer->renderAllActive (elapsed );
	windowInterface->update ( );
	}


void GameLoopSystem::Reload()
{
	

	

}
#include "GameLoopSystem.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
	}
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"


GameLoopSystem::GameLoopSystem ()
	{};


void GameLoopSystem::linkWithInterface(RenderingSystem* Renderer, InputSystem* InputManager)
{
	this->Renderer= Renderer;
	windowInterface = this->Renderer->getWindow();
	this->InputManager = InputManager;
}

void GameLoopSystem::clockFrame ()
{
	current = clock ( );
	elapsed = current - previous;
	previous = current;
	lag += elapsed;
}

void GameLoopSystem::DoMainLoop ()
{	
	while (InputManager->getGameState())
		{		
		clockFrame ();
		getInput ( );
		
		while ( lag >= 17 )
			updateGameState ();
		
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
	InputManager->processInput();	
	lag -= 17;	
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
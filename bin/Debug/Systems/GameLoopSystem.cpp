#include "GameLoopSystem.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
	}
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"


GameLoopSystem::GameLoopSystem ( RenderingSystem* RenderSystem,InputSystem* InputsSystem)
	{
	RSYS = RenderSystem;
	WSYS = RSYS->getWindow ();
	ISYS = InputsSystem;
	
	};

void GameLoopSystem::DoMainLoop ()
	{
	while (ISYS->getGameState())
		{
		//game_active = ISYS->getGameState();
		//game_state = ISYS->game_state;
		current = clock ( );
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		getInput ( );
		//not ideal; input should be registered in process input;input should be processed in updateGameState()
		if ( RSYS->entityType == "UI" || RSYS->entityType == "UI+OBJ" )
		{

			while (lag >= 250)
				updateGameState(true);
		}
		else
		{
			while (lag >= 10)
				updateGameState(false);
		}
		ISYS->resetInput();
		renderScreen ( );

		}
	}

void GameLoopSystem::getInput ()
	{
	WSYS->clear ( );
	ISYS->getInput();
	}

void GameLoopSystem::updateGameState ( bool throttle)
	{
	/*if (game_state == "Reload")
		Reload();*/


	if (RSYS->entityType == "UI")
		{
			ISYS->processInput(throttle);	
			lag -= 250;
		}
	else 
		if(RSYS->entityType=="OBJ")
		{
		ISYS->processInput(throttle);
		lag -= 10;
		}
	else
	if ( RSYS->entityType == "UI+OBJ" )
		{
		ISYS->processInput ( throttle );
		lag -= 45;
		}
	


	}

void GameLoopSystem::renderScreen ()
	{
	RSYS->renderAllActive (elapsed );
	WSYS->update ( );
	}


void GameLoopSystem::Reload()
{
	

	

}
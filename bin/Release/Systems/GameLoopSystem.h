#pragma once

#include <map>
#include <string>
#include <typeindex>
#include <iostream>
#include <list>
#include "../EntityComponents/Entity.h"
#include "../Extras/window/window.h"
#include <time.h>
#include "RenderingSystem.h"
#include "InputSystem.h"
class GameLoopSystem
	{

	public:

		GameLoopSystem ( RenderingSystem* RenderSystem, InputSystem* InputsSystem );
		~GameLoopSystem ( );
		void DoMainLoop ();

		
		void getInput ();
		void updateGameState(bool throttle);
		void renderScreen ();
		void Reload();



	

	private:
		std::list<Entity*> EntityList;
		Window* WSYS;
		RenderingSystem* RSYS;
		InputSystem* ISYS;
		bool game_active = true;		
		std::string game_state;
		double current, elapsed;
		double previous = clock ( );
		double lag = 0.0;

	};
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

		GameLoopSystem ( );
		~GameLoopSystem ( );
		void linkWithInterface(RenderingSystem* Renderer, InputSystem* InputManager);


		void DoMainLoop ();

		
		void getInput ();
		void updateGameState(bool throttle);
		void renderScreen ();
		void Reload();



	

	private:
		RenderingSystem* Renderer;
		InputSystem* InputManager;
		Window* windowInterface;

		std::list<Entity*> EntityList;
		bool game_active = true;		
		std::string game_state;
		double current, elapsed;
		double previous = clock ( );
		double lag = 0.0;

	};
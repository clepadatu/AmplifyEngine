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
		//Constructor
		GameLoopSystem ( );
		//Destructor
		~GameLoopSystem ( );
		// Provide hooks to Renderer and InputManager
		void linkWithInterface(RenderingSystem* Renderer, InputSystem* InputManager);
		// Frame tracker routine; call to provide metrics used in FPS calculus
		void clockFrame ();
		// Execute Game Loop
		void DoMainLoop ();

		// First step in Game Loop; query any pressed keys and store result for later processing 
		void getInput ();
		// Second step in Game Loop; Periodic game state update function; this needs to be executed once every couple of frames, in order to produce smooth transition across multiple platforms
		void updateGameState();
		// Last step in Game Loop; Trigger rendering of all active objects to the screen
		void renderScreen ();
		// Not used
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
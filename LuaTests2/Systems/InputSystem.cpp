#include "InputSystem.h"
#include "SceneManager.h"

//======================================= CONSTRUCTORS AND MAINTENANCE =================================

InputSystem::InputSystem ( )
	{
	delay = 0;		
	menuDirection = 0;
	game_running = true;
	game_status = "Work";
	}

void InputSystem::linkWithInterface(RenderingSystem* Renderer, CollisionSystem* Collisions, SceneManager* StageManager)
{
	this->Renderer = Renderer;
	windowInterface = this->Renderer->getWindow();
	this->Collisions = Collisions;
	this->StageManager = StageManager;

}

InputSystem::~InputSystem ()
	{}

bool InputSystem::getGameState ( )
	{
	return game_running;
	}
void InputSystem::closeGame ( )
	{
	game_running = false;
	}

void InputSystem::resetInput ( )//Delay reset/substract
	{
	delay -= 5;
	}

//=========================================================================================================

//======================================= INPUT PROCESSORS =================================
void InputSystem::processInput ( bool whiletrue )
	{
	if ( whiletrue )
		{
		while ( delay <= 0 )
			{
			//Active Current Option menu data internal in MenuComponent
			//Multiple Input Types functions based on Entity types
			if ( inputTypeReq == "UI" )
				processMenuInput ( );
			else if ( inputTypeReq == "Gameplay" )
				processGameplayInput ( );
			}
		}
	else
		{
		if ( inputTypeReq == "UI" )
			processMenuInput ( );
		else if ( inputTypeReq == "Gameplay" )
			processGameplayInput ( );
		}
	}

void InputSystem::processMenuInput()
{
	
	switch (getActiveMenu())
	{
		case 10:
		{				
			setActiveOption();
			processMenuSelection();			
			delay = 100;
			break;
		}
		case 11:
		{
			setActiveOption();
			processMenuSelection();
			delay = 100;
			break;
		}

		default:
			setActiveOption();
			processMenuSelection();
			delay = 100;
			break;	
	}
	menuDirection = 0;
	ActiveMenu->get<MenuComponent>()->selection = false;
}

void InputSystem::processGameplayInput()
{
	switch (getActiveLevel())
	{
		case 1:
			processPlayerInput ();
			//delay = 17;
			break;
		case 2:

			delay = 125;
			break;
		case 9://Default - travel
			delay = 125;
			break;
	}
}

//=========================================================================================================


//======================================= MENU, LEVEL AND ENTITIES LOADERS =================================

void InputSystem::setMenus ( std::list<Entity*> Entities, std::string type ) //Set Active menu Entity data
	{
	MenuList = Entities;
	inputTypeReq = type;
	setActiveMenu ( );
	}
void InputSystem::setLevels ( std::list<Entity*> Entities, std::string type )//Set Initial List of Levels
	{
	LevelList = Entities;
	setActiveLevel ( ); // NO FEATURE - need to have Level enabled from config file / need to pass through ID to activate, and reload Entities afterwards; In the future;
	}
void InputSystem::setLevelEntities ( std::list<Entity*> Entities, std::string type ) //Set Initial List of Entities, or reload different Entities
	{
	EntityList = Entities;
	inputTypeReq = type;
	detectPlayer ();
	}

void InputSystem::setAmmo ( std::list<Entity*> Entities, std::string type )
	{
	AmmoList = Entities;
	}
//=========================================================================================================




//======================================= MENU & LEVEL DEACTIVATORS =================================

void InputSystem::deactivateLevel ( Entity* level )
	{
	level->get<LevelComponent> ( )->Active = false;
	}

void InputSystem::deactivateMenu ( Entity* menu )
	{
	menu->get<MenuComponent> ( )->Active = false;
	}

//=========================================================================================================

void InputSystem::detectPlayer ()
	{
	std::list<Entity*>::iterator i = EntityList.begin ();
	while ( i != EntityList.end () )
		{
		if ( (*i)->getType () == "Player" )
			{
			Player = (*i);
			break;
			}
		++i;
		}
	}


//======================================= MENU & LEVEL SETTERS AND GETTERS =================================

void InputSystem::setActiveMenu ( )
	{
	std::list<Entity*>::iterator i = MenuList.begin ( );
	while ( i != MenuList.end ( ) )
		{
		if ( (*i)->get<MenuComponent> ( )->Active == true )
			{
			ActiveMenu = (*i);
			break;
			}
		++i;
		}
	}

void InputSystem::setActiveMenu ( int UID )
	{
	std::list<Entity*>::iterator i = MenuList.begin ( );
	while ( i != MenuList.end ( ) )
		{
		if ( (*i)->get<MenuComponent> ( )->thisMenu.ID == UID )
			{
			(*i)->get<MenuComponent> ( )->Active = true;
			ActiveMenu = (*i);
			ActiveMenu->get<MenuComponent> ( )->Active = true;
			break;
			}
		++i;
		}

	}


int InputSystem::getActiveMenu ( )
	{
	std::list<Entity*>::iterator i = MenuList.begin ( );
	while ( i != MenuList.end ( ) )
		{
		if ( (*i)->get<MenuComponent> ( )->Active == true )
			{
			return (*i)->get<MenuComponent> ( )->thisMenu.ID;
			break;
			}
		++i;
		}

	}

void InputSystem::setActiveLevel ( )
	{
	std::list<Entity*>::iterator i = LevelList.begin ( );
	while ( i != LevelList.end ( ) )
		{
		if ( (*i)->get<LevelComponent> ( )->Active == true )
			{
			ActiveLevel = (*i);
			break;
			}
		++i;
		}
	}

void InputSystem::setActiveLevel ( int UID )
	{
	std::list<Entity*>::iterator i = LevelList.begin ( );
	while ( i != LevelList.end ( ) )
		{
		if ( (*i)->get<LevelComponent> ( )->ID == UID )
			{
			(*i)->get<LevelComponent> ( )->Active == true;
			ActiveLevel = (*i);
			break;
			}
		++i;
		}
	}

int InputSystem::getActiveLevel ( )
	{
	std::list<Entity*>::iterator i = LevelList.begin ( );
	while ( i != LevelList.end ( ) )
		{
		if ( (*i)->get<LevelComponent> ( )->Active == true )
			{
			return (*i)->get<LevelComponent> ( )->ID;
			break;
			}
		++i;
		}
	}
//=========================================================================================================





//======================================= MENU NAVIGATION =================================


void InputSystem::getInput ( )
	{
	if ( delay <= 0 )
		{
		if ( inputTypeReq == "UI" )
			pollMenuKeys ();
		else
			pollGameplayKeys ();
		}
	//else if (inputTypeReq == "Gameplay")

	}

void InputSystem::pollGameplayKeys ( )
	{
	if ( keyDownPressed ( ) )
		yAxis = -1;
	if ( keyUpPressed ( ) )
		yAxis = 1;
	if ( keyLeftPressed ( ) )
		xAxis = -1;
	if ( keyRightPressed ( ) )
		xAxis = 1;
	if ( keyEscapePressed () )
		{
		inputTypeReq = "UI";
		//deactivateMenu ( ActiveMenu );
		//DEBUG std::cout << "newID=" << new_ID << std::endl;
		Renderer->enableUIOBJ ();

		setActiveMenu (11);
		}
	if ( keySpacePressed () )
		launched = true;
	/*if ( keyConfirmPressed ( ) )
		ActiveMenu->get<MenuComponent> ( )->selection = true;*/
	windowInterface->getMousePosition(mouse_x, mouse_y);
	}
void InputSystem::processPlayerInput ()
	{
	
	Player->get<GraphicsComponent>()->PlayerUpdate(Renderer->Check_resize(), xAxis, yAxis, windowInterface, mouse_x, mouse_y);
	if ( launched && countdown() )
		ActivateProjectile ();
	UpdateProjectiles ();
	DoCollisions ();
	xAxis = 0;
	yAxis = 0;
	launched = false;
	}


bool InputSystem::keyDPressed ()
	{
	if ( windowInterface->isKeyPressed ( 68 ) )
		return true;
	else
		return false;
	}

void InputSystem::pollMenuKeys ( )
	{
	if ( keyDownPressed ( ) )
		menuDirection = 1;
	if ( keyUpPressed ( ) )
		menuDirection = -1;
	if ( keyConfirmPressed ( ) )
		ActiveMenu->get<MenuComponent> ( )->selection = true;
	}

bool InputSystem::keyUpPressed ( )
	{
	if ( windowInterface->isKeyPressed ( 265 ) )
		return true;
	else
		return false;
	}

bool InputSystem::keyDownPressed ( )
	{
	if ( windowInterface->isKeyPressed ( 264 ) )
		return true;
	else
		return false;
	}

bool InputSystem::keyLeftPressed ( )
	{
	if ( windowInterface->isKeyPressed ( 263 ) )
		return true;
	else
		return false;
	}

bool InputSystem::keyRightPressed ( )
	{
	if ( windowInterface->isKeyPressed ( 262 ) )
		return true;
	else
		return false;
	}

bool InputSystem::keyEscapePressed ()
	{
	if ( windowInterface->isKeyPressed ( 256 ) )
		return true;
	else
		return false;

	}

bool InputSystem::keyConfirmPressed ( )
	{
	if ( windowInterface->isKeyPressed ( 257 ) )
		return true;
	else
		return false;
	}

bool InputSystem::keySpacePressed ( )
	{
	if ( windowInterface->isKeyPressed ( 32 ) )
		return true;
	else
		return false;
	}

void InputSystem::setActiveOption ( )
	{
	switch ( menuDirection )
		{
			case 1:
				ActiveMenu->get<MenuComponent> ( )->incrementActiveItem ( );
				break;
			case -1:
				ActiveMenu->get<MenuComponent> ( )->decrementActiveItem ( );
				break;
			default:
				break;
		}
	menuDirection = 0;
	}

void InputSystem::processMenuSelection ( )
	{
	if ( ActiveMenu->get<MenuComponent> ( )->selection == true )
		{
		int new_ID = ActiveMenu->get<MenuComponent> ( )->ActiveSelectionID ( );
		switch ( new_ID )
			{
			//See ManiMenu.LUA->IDvec
				case 0:
					game_status = "Shutdown";
					closeGame ( );
					
					break;
				case 1:
					//Go Gameplay
					req_id = new_ID;
					game_status = "Reload";
					ActiveMenu->get<MenuComponent> ()->selection = false;
					deactivateMenu ( ActiveMenu );
					inputTypeReq = "Gameplay";
					Renderer->enableOBJOnly ();
					/*closeGame ( );*/
					break;
				case -1:
					Renderer->NA_Selector = true;
					ActiveMenu->get<MenuComponent> ( )->selection = false;
					break;
				case -2:
					inputTypeReq = "Gameplay";
					//deactivateMenu ( ActiveMenu );
					//DEBUG std::cout << "newID=" << new_ID << std::endl;
					Renderer->enableOBJOnly ( );
					ActiveMenu->get<MenuComponent> ( )->selection = false;
					deactivateMenu ( ActiveMenu );
					break;
				case 10:
					inputTypeReq = "UI";
					//deactivateMenu ( ActiveMenu );
					//DEBUG std::cout << "newID=" << new_ID << std::endl;
					Renderer->enableUIOnly ( );
					ResetOBJs ();
					ActiveMenu->get<MenuComponent> ( )->selection = false;
					deactivateMenu ( ActiveMenu );
					setActiveMenu ( new_ID );
					break;
				default:
					//Go Menu
					ActiveMenu->get<MenuComponent> ( )->selection = false;
					deactivateMenu ( ActiveMenu );
					//DEBUG std::cout << "newID=" << new_ID << std::endl; 
					setActiveMenu ( new_ID );
					//DEBUG std::cout << "ID=" << ActiveMenu->get<MenuComponent>()->thisMenu.ID << " is active=" << ActiveMenu->get<MenuComponent>()->Active << std::endl;
					break;
			}
		}
	}

//=========================================================================================================

void InputSystem::ActivateProjectile ()
	{
	for ( auto&i : AmmoList )
		{
		if ( (*i).get<GraphicsComponent> ()->active == false )
			{
			(*i).get<GraphicsComponent> ()->active = true;
			(*i).get<GraphicsComponent> ()->Reinit_pos ( Player->get<GraphicsComponent> ()->playerGetPosition () );
			(*i).get<GraphicsComponent> ()->Initialise_controls ( windowInterface->getWidth (), windowInterface->getHeight (), 1, i->get <GraphicsComponent> ()->position_x, i->get <GraphicsComponent> ()->position_y );
			break;
			}
		}
	}

void InputSystem::UpdateProjectiles ()
	{
	for ( auto&i : AmmoList )
		{
		if ( (*i).get<GraphicsComponent> ()->active == true )
			{
			if ( (*i).get<GraphicsComponent> ()->_Should_draw ( windowInterface ) )
				(*i).get<GraphicsComponent> ()->update_projectile ();

			}

		}

	}

void InputSystem::DoCollisions ()
	{

	Collisions->DoCollision ( EntityList, AmmoList );

	//for ( auto&i : AmmoList )
	//	{
	//	if ( (*i).get<GraphicsComponent> ( )->active == true )
	//		{
	//		/*if ( (*i).get<GraphicsComponent> ( )->_Should_draw ( windowInterface ) )
	//			(*i).get<GraphicsComponent> ( )->update_projectile ( );*/
	//		for ( auto&k : EntityList )
	//			{
	//			if ( (*k).get<GraphicsComponent> ()->destroyed == false )
	//				{

	//				}
	//			}

	//		}

	//	}

	}


bool InputSystem::countdown ( )
	{
	if ( CD_Start == 0 )
		{
		CD_Start= clock ( );
		}
	double seconds_passed = (clock ( ) - CD_Start) / CLOCKS_PER_SEC;
	if ( seconds_passed >= CD_delay )
		{		
		CD_Start= 0;
		return true;
		}
	return false;
	}

void InputSystem::ResetOBJs ()
	{
	Renderer->setOBJ ( StageManager->getOBJ () );
	for ( auto&i : StageManager->getOBJ () )
		{
		(*i).get<GraphicsComponent> ()->destroyed = false;
		}
	}
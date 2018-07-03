#include "RenderingSystem.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
	}
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"


RenderingSystem::RenderingSystem (  )
	{
	selector = ">";
	srand ( time ( NULL ) );
	loadSettings ( );
	WSYS = new Window ( "Amplify", Window_width, Window_height, Window_fullscreen );
	if ( WSYS->init_OK )
		{
		std::cout << "OpenGL Window initialised correctly." << std::endl;		
		}
	WSYS->WindowColor ( 0.0f, 0.0f, 0.0f, 0.3f );
	glEnable ( GL_DEPTH_TEST );
	glDepthFunc ( GL_LEQUAL );
	glEnable ( GL_BLEND );
	//	glEnable ( GL_CULL_FACE );
	glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 0);
	glLineWidth(2);

	};
void RenderingSystem::Reset()
{
	entityType = "";
	for (Entity* ptr : EntityList) delete ptr;
	EntityList.clear();

}

void RenderingSystem::enableUIOnly ()
	{
	entityType = "UI";
	}
void RenderingSystem::enableOBJOnly ()
	{
	entityType = "OBJ";
	}
void RenderingSystem::enableUIOBJ ()
	{
	entityType = "UI+OBJ";
	}

void RenderingSystem::setUI ( std::list<Entity*> Entities )
	{
	UI = Entities;
	for ( auto const& i : UI )
		{
		i->get<TextComponent> ( )->Initialise_controls ( Window_width, Window_height, 1 );
		i->get<TextComponent> ( )->enableShader ( );
		}

	}

void RenderingSystem::setAmmo ( std::list<Entity*> Entities )
	{
	Ammo = Entities;
	glm::vec2 position;
	glm::vec2 direction;
	for ( auto const&i : OBJ )
		{
		if ( i->getType () == "Player" )
			{
			position = i->get<GraphicsComponent> ()->playerGetPosition ();
			direction = i->get<GraphicsComponent> ( )->playerGetFacingDirection( );
			
			}
		}
	for ( auto const& i : Ammo )
		{
		i->get<GraphicsComponent> ()->setupProjectile ( position, direction, 0.02f );

		i->get<GraphicsComponent> ()->Initialise_controls ( Window_width, Window_height, 1, i->get <GraphicsComponent> ()->position_x, i->get <GraphicsComponent> ()->position_y );
		i->get<GraphicsComponent> ( )->enableShader ( );
		}
	}

void RenderingSystem::setOBJ ( std::list<Entity*> Entities)
	{
	OBJ = Entities;
	for ( auto const& i : OBJ )
		{
		//switch (i->getType()) only works with char type, not string
		if ( i->getType ( ) == "ghost" || i->getType ( ) == "SuperGhost" )
			{

			//			i->get<GraphicsComponent>()->setScreenData(Window_width,Window_height);
			i->get<GraphicsComponent> ( )->Initialise_controls ( Window_width, Window_height, 1, rand ( ) % Window_width, rand ( ) % (Window_height / 2) + 15 );
			i->get<GraphicsComponent> ( )->enableShader ( );
			}
		else
		if ( i->getType ( ) == "Player" )
			{
			WSYS->getMousePosition ( mouse_x, mouse_y );
			std::cout << "mousex=" << mouse_x << " mousey=" << mouse_y << std::endl;
			i->get<GraphicsComponent> ( )->Initialise_controls ( Window_width, Window_height, 1, rand ( ) % Window_width, rand ( ) % (Window_height / 3) + 15 );
			i->get<GraphicsComponent> ( )->enableShader ( );
			}
		else
		if ( i->getType ( ) == "Background" )
			{
			i->get<GraphicsComponent> ( )->Initialise_controls ( Window_width, Window_height, 1, i->get<GraphicsComponent> ( )->position_x, i->get<GraphicsComponent> ( )->position_y );
			i->get<GraphicsComponent> ( )->enableShader ( );
			}
		}
	}

//void RenderingSystem::setEntities ( std::list<Entity*> Entities, std::string type )
//	{
//	entityType = type;
//	EntityList = Entities;
//	if ( entityType == "UI" )
//		{
//		for ( auto const& i : EntityList )
//			{
//				i->get<TextComponent> ( )->Initialise_controls ( Window_width, Window_height, 1);
//				i->get<TextComponent> ( )->enableShader ( );
//			}
//
//		}
//
//	if ( entityType == "Level" )
//		{
//		}
//	if ( entityType == "OBJ" )
//		{
//
//		for ( auto const& i : EntityList )
//			{
//			//switch (i->getType()) only works with char type, not string
//			if ( i->getType () == "ghost" || i->getType () == "SuperGhost" )
//				{
//
//				//			i->get<GraphicsComponent>()->setScreenData(Window_width,Window_height);
//				i->get<GraphicsComponent> ()->Initialise_controls ( Window_width, Window_height, 1, rand () % Window_width, rand () % (Window_height / 3) + 60 );
//				i->get<GraphicsComponent> ()->enableShader ();
//				}
//			else
//			if ( i->getType () == "Player" )
//				{
//				WSYS->getMousePosition ( mouse_x, mouse_y );
//				std::cout << "mousex=" << mouse_x << " mousey=" << mouse_y << std::endl;
//				i->get<GraphicsComponent> ()->Initialise_controls ( Window_width, Window_height, 1, rand () % Window_width, rand () % (Window_height / 3) + 60 );
//				i->get<GraphicsComponent> ()->enableShader ();
//				}
//			else 
//			if ( i->getType () == "Background" )
//				{
//				i->get<GraphicsComponent> ( )->Initialise_controls ( Window_width, Window_height, 1, i->get<GraphicsComponent> ( )->position_x, i->get<GraphicsComponent> ( )->position_y );
//				i->get<GraphicsComponent> ( )->enableShader ( );
//				}
//			}
//		}
//	}

void RenderingSystem::loadSettings ( )
	{
	using namespace luabridge;
	lua_State* L = luaL_newstate ( );
	luaL_openlibs ( L );

	luaL_dofile ( L, "Scripts/settings.lua" );


	Window_fullscreen = getGlobal ( L, "fullscreen" ).cast<int> ( );
	Window_height = getGlobal ( L, "height" ).cast<int> ( );
	Window_width = getGlobal ( L, "width" ).cast<int> ( );
	}




void RenderingSystem::renderAllActive ( double elapsed) 
	{
	timerFPS = elapsed;
	if ( entityType == "UI" )
		{
		renderBackground ();
		for ( auto const& i : UI )
			{
			renderMenuItems ( i );
			}
		}
	else
	if ( entityType == "OBJ" )
		{
		for ( auto const& i : OBJ )
			{
			if ( i->get<GraphicsComponent> ( )->destroyed == false )
			renderItem ( i );
			}
		for ( auto const&i : Ammo )
			{
			if ( i->get<GraphicsComponent> ( )->active )
				renderItem ( i );
			}
		}
	else
	if ( entityType == "UI+OBJ" )
		{
		for ( auto const& i : OBJ )
			{
			if ( i->get<GraphicsComponent> ( )->destroyed==false)
			renderItem ( i );
			}
		for ( auto const& i : UI )
			{
			renderMenuItems ( i );
			}
		for ( auto const&i : Ammo )
			{
			if ( i->get<GraphicsComponent> ()->active )
				renderItem ( i );
			}
		}

	//for ( auto const& i : EntityList )
	//	{
	//	if (entityType == "UI")
	//	{
	//		//DEBUG std::cout << "MenuID=" << i->get<MenuComponent>()->thisMenu.ID << " is active=" << i->get<MenuComponent>()->Active << std::endl; 
	//		renderMenuItems(i);
	//	}
	//	else
	//		renderItem(i);



	//	//if ( //insert test if active menu, in case of menu and all other lelel/obj, to avoid overlap )
	//	}
	
	}

void RenderingSystem::renderBackground ()
	{
	GraphicsComponent* temp=NULL;
	for ( auto const& i : OBJ )
		{
		if ( i->getType ( ) == "Background" )
			temp = i->get<GraphicsComponent> ( );
		}
	temp->enableShaderonly ( );
	temp->computeMatrices ( );
	temp->bind ( );
	temp->texture_activate ( );
	temp->Draw ( );
	temp->unbind ( );
	}

void RenderingSystem::countdown ()
	{
	if ( NA_start == 0 )
		{
		NA_start = clock ();
		}
	double seconds_passed = (clock () - NA_start) / CLOCKS_PER_SEC;
	if ( seconds_passed >= NA_delay )
		{
		NA_Selector = false;
		NA_start = 0;
		}
	}

void RenderingSystem::renderDefault ()
	{
	if ( goodbye )
		{
		WSYS->clear ( );
		for ( auto const& item : UI )
			{
			textObj = item->get<TextComponent> ( );
			textObjProp = item->get<MenuComponent> ( );
			if ( textObjProp->Active==true )
				textObj->render_text ( "Title", 0.4f, WSYS->getWidth () * 10 / 100, WSYS->getHeight () * 45 / 100, 0, textObjProp->Misc, "green" );
			}
		WSYS->update ( );
	
		}
	}

void RenderingSystem::renderMenuItems(Entity* item)
{

if ( NA_Selector)
	{
	countdown ();
	textObj = item->get<TextComponent> ( );
	textObjProp = item->get<MenuComponent> ( );
	textObj->render_text ( "Title", 0.9f, WSYS->getWidth ( ) * 20 / 100, WSYS->getHeight ( ) * 15 / 100, 0, "Illusions, the Game", "green" );
	//textObj->render_text ( "Title", 0.3f, WSYS->getWidth ( ) * 20 / 100, WSYS->getHeight ( ) * 40 / 100, 0, textObjProp->thisMenu.Name, "green" );
	textObj->render_text ( "Title", 0.7f, WSYS->getWidth ( ) * 30 / 100, WSYS->getHeight ( ) * 50 / 100, 0, textObjProp->NA, "green" );
	textObj->render_text ( "FPS", 0.6f, WSYS->getWidth ( ) * 5 / 100, WSYS->getHeight ( ) * 5 / 100, CLOCKS_PER_SEC / timerFPS, "FPS:", "green" );	
	}
else if (item->get<MenuComponent>()->Active == true)
	{
		textObj = item->get<TextComponent>();
		textObjProp = item->get<MenuComponent>();
		textObj->render_text("Title", 0.9f, WSYS->getWidth() * 20 / 100, WSYS->getHeight() * 15 / 100, 0, "Illusions, the Game", "green");
		textObj->render_text("Title", 0.8f, WSYS->getWidth() * 20 / 100, WSYS->getHeight() * 40 / 100, 0, textObjProp->thisMenu.Name, "green");
		auto map = textObjProp->returnAllOptionItems();
		
		for (auto iter : map)
		{		/*std::cout << "Test2";
				std::cout << iter.<< std::endl;*/
			if (iter.first == textObjProp->returnOptionID())
				textObj->render_text ( "Title", 0.8f, WSYS->getWidth ( ) * iter.second.position_x / 100, WSYS->getHeight ( ) * iter.second.position_y/ 100, 0, iter.second.Name,"red");
			else 
				textObj->render_text("Title", 0.8f, WSYS->getWidth() * iter.second.position_x / 100, WSYS->getHeight() * iter.second.position_y / 100, 0, iter.second.Name, "green");
					
		}
		textObj->render_text ( "FPS", 0.6f, WSYS->getWidth () * 5 / 100, WSYS->getHeight () * 5 / 100, CLOCKS_PER_SEC/timerFPS, "FPS:","green" );
		
	}

	
}

void RenderingSystem::renderItem (Entity* item )
	{
	
		
		Obj = item->get<GraphicsComponent> ();
	
		Obj->enableShaderonly ( );
		
		
		if ( item->getType ( ) != "Player" && item->getType ( ) != "Background" &&item->getType()!="PlayerProjectile")
			Obj->computeAIMovement();	
		if ( item->getType ( ) == "PlayerProjectile" )
			Obj->projectileComputeMatrices ( );
		else 
			Obj->computeMatrices ();
		Obj->bind ( );
		Obj->texture_activate ( );
		Obj->Draw ( );
		Obj->unbind ( );
		
	}

bool RenderingSystem::Check_resize ( )
	{
	if ( Window_width != WSYS->getWidth ( ) )
		return 1;
	if ( Window_height != WSYS->getHeight ( ) )
		return 1;
	return 0;
	}
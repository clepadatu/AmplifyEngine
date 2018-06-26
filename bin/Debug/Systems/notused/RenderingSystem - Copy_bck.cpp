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
void RenderingSystem::setEntities ( std::list<Entity*> Entities, std::string type )
	{
	entityType = type;
	EntityList = Entities;
	if ( entityType == "Menu" )
		{
		for ( auto const& i : EntityList )
			{
						
				i->get<TextComponent> ( )->Initialise_controls ( Window_width, Window_height, 1);
				i->get<TextComponent> ( )->enableShader ( );
							
			}

		}

	if ( entityType == "Level" )
		{
		}
	if ( entityType == "OBJ" )
		{

		for ( auto const& i : EntityList )
			{
			//switch (i->getType()) only works with char type, not string
			if ( i->getType () == "ghost" || i->getType () == "SuperGhost" )
				{

				//			i->get<GraphicsComponent>()->setScreenData(Window_width,Window_height);
				i->get<GraphicsComponent> ()->Initialise_controls ( Window_width, Window_height, 1, rand () % Window_width, rand () % (Window_height / 3) + 60 );
				i->get<GraphicsComponent> ()->enableShader ();
				}
			else
			if ( i->getType () == "Player" )
				{
				WSYS->getMousePosition ( mouse_x, mouse_y );
				std::cout << "mousex=" << mouse_x << " mousey=" << mouse_y << std::endl;
				i->get<GraphicsComponent> ()->Initialise_controls ( Window_width, Window_height, 1, rand () % Window_width, rand () % (Window_height / 3) + 60 );
				i->get<GraphicsComponent> ()->enableShader ();
				}
			}
		}
	}

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
	for ( auto const& i : EntityList )
		{
		if (entityType == "Menu")
		{
			//DEBUG std::cout << "MenuID=" << i->get<MenuComponent>()->thisMenu.ID << " is active=" << i->get<MenuComponent>()->Active << std::endl; 
			renderMenuItems(i);
		}
		else
			renderItem(i);



		//if ( //insert test if active menu, in case of menu and all other lelel/obj, to avoid overlap )
		}
	
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

void RenderingSystem::renderMenuItems(Entity* item)
{
if ( NA_Selector)
	{
	countdown ();
	textObj = item->get<TextComponent> ( );
	textObjProp = item->get<MenuComponent> ( );
	textObj->render_text ( "Title", 0.4f, WSYS->getWidth ( ) * 20 / 100, WSYS->getHeight ( ) * 15 / 100, 0, "Illusions, the Game", "green" );
	//textObj->render_text ( "Title", 0.3f, WSYS->getWidth ( ) * 20 / 100, WSYS->getHeight ( ) * 40 / 100, 0, textObjProp->thisMenu.Name, "green" );
	textObj->render_text ( "Title", 0.3f, WSYS->getWidth ( ) * 30 / 100, WSYS->getHeight ( ) * 50 / 100, 0, textObjProp->NA, "green" );
	textObj->render_text ( "FPS", 0.2f, WSYS->getWidth ( ) * 5 / 100, WSYS->getHeight ( ) * 5 / 100, CLOCKS_PER_SEC / timerFPS, "FPS:", "green" );	
	}
else if (item->get<MenuComponent>()->Active == true)
	{
		textObj = item->get<TextComponent>();
		textObjProp = item->get<MenuComponent>();
		textObj->render_text("Title", 0.4f, WSYS->getWidth() * 20 / 100, WSYS->getHeight() * 15 / 100, 0, "Illusions, the Game", "green");
		textObj->render_text("Title", 0.3f, WSYS->getWidth() * 20 / 100, WSYS->getHeight() * 40 / 100, 0, textObjProp->thisMenu.Name, "green");
		auto map = textObjProp->returnAllOptionItems();
		
		for (auto iter : map)
		{		/*std::cout << "Test2";
				std::cout << iter.<< std::endl;*/
			if (iter.first == textObjProp->returnOptionID())
				textObj->render_text ( "Title", 0.3f, WSYS->getWidth ( ) * iter.second.position_x / 100, WSYS->getHeight ( ) * iter.second.position_y/ 100, 0, iter.second.Name,"red");
			else 
				textObj->render_text("Title", 0.3f, WSYS->getWidth() * iter.second.position_x / 100, WSYS->getHeight() * iter.second.position_y / 100, 0, iter.second.Name, "green");
					
		}
		/*	if (option.first == textObjProp->returnOptionID())
				textObj->render_text("Title", 0.3f, WSYS->getWidth() * option.second.position_x / 100, WSYS->getHeight() * option.second.position_y / 100, 0, option.second.Name, "red");
			else
				textObj->render_text("Title", 0.3f, WSYS->getWidth() * option.second.position_x / 100, WSYS->getHeight() * option.second.position_y / 100, 0, option.second.Name, "");
		}*/
	//	switch (textObjProp->returnOptionID())
	//	{
	//	case 0:		
	//		
	///*		textObj->render_text("Title", 0.3f, WSYS->getWidth() * 10 / 100, WSYS->getHeight() * 50 / 100, 0, textObjProp->Option1,"red");
	//		textObj->render_text("Title", 0.3f, WSYS->getWidth() * 10 / 100, WSYS->getHeight() * 55 / 100, 0, textObjProp->Option2,"");
	//		textObj->render_text("Title", 0.3f, WSYS->getWidth() * 10 / 100, WSYS->getHeight() * 65 / 100, 0, textObjProp->Option3,"");*/
	//		break;
	//	case 1:			
	//		textObj->render_text ( "Title", 0.3f, WSYS->getWidth ( ) * 10 / 100, WSYS->getHeight ( ) * 50 / 100, 0, textObjProp->Option1, "" );
	//		textObj->render_text ( "Title", 0.3f, WSYS->getWidth ( ) * 10 / 100, WSYS->getHeight ( ) * 55 / 100, 0, textObjProp->Option2, "red" );
	//		textObj->render_text ( "Title", 0.3f, WSYS->getWidth ( ) * 10 / 100, WSYS->getHeight ( ) * 65 / 100, 0, textObjProp->Option3, "" );
	//		break;
	//	case 2:
	//		textObj->render_text ( "Title", 0.3f, WSYS->getWidth ( ) * 10 / 100, WSYS->getHeight ( ) * 50 / 100, 0, textObjProp->Option1, "" );
	//		textObj->render_text ( "Title", 0.3f, WSYS->getWidth ( ) * 10 / 100, WSYS->getHeight ( ) * 55 / 100, 0, textObjProp->Option2, "" );
	//		textObj->render_text ( "Title", 0.3f, WSYS->getWidth ( ) * 10 / 100, WSYS->getHeight ( ) * 65 / 100, 0, textObjProp->Option3, "red" );
	//		break;
	//	}
		textObj->render_text ( "FPS", 0.2f, WSYS->getWidth () * 5 / 100, WSYS->getHeight () * 5 / 100, CLOCKS_PER_SEC/timerFPS, "FPS:","green" );
		/*textObj->render_text ( );
		textObj->render_text ( );
		textObj->render_text ( );*/
	}
}

void RenderingSystem::renderItem (Entity* item )
	{
	
		
		Obj = item->get<GraphicsComponent> ();
	
		Obj->enableShaderonly ( );
		if (item->getType() != "Player")
			Obj->computeAIMovement();
		Obj->computeMatrices ( );
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
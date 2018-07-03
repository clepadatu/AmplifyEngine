#pragma once

#include <map>
#include <string>
#include <typeindex>
#include <iostream>
#include <list>
#include "../EntityComponents/Entity.h"
#include "../EntityComponents/GraphicsComponent.h"
#include "../EntityComponents/TextComponent.h"
#include "../EntityComponents/MenuComponent.h"
#include "../Extras/window/window.h"
#include <time.h>

class RenderingSystem {

public:

	RenderingSystem (  );
	~RenderingSystem();


	void loadSettings ( );
	void renderAllActive (double elapsed);
	void renderMenuItems(Entity* item);
	void renderItem ( Entity* item );
	void renderBackground ();
	void renderDefault ();

	void addEntity(Entity* e);
	std::list<Entity*> getEntities() const{ return EntityList; };
	void setEntities ( std::list<Entity*> Entities, std::string type );

	//new
	void setUI ( std::list<Entity*> Entities);
	void setOBJ ( std::list<Entity*> Entities);
	void setAmmo ( std::list<Entity*> Entities );
	//new
	void enableUIOnly ();
	void enableOBJOnly ( );
	void enableUIOBJ ( );

	void Reset();
	void countdown ();

	Window* getWindow () const { return WSYS; };

	bool Check_resize ();
		

	std::string entityType; // Menu/Level/OBJ
private:
	std::list<Entity*> EntityList;

	std::list<Entity*> OBJ;
	std::list<Entity*> UI;
	std::list<Entity*> Ammo;
	
	Window* WSYS;
	int Window_fullscreen;
	int Window_height;
	int Window_width;

	double mouse_x;
	double mouse_y;

	double timerFPS;


public:
	bool NA_Selector = false;
	clock_t NA_start=0;
	double NA_delay = 3;

	bool goodbye = false;

	std::string selector;
private:
	GraphicsComponent* Obj;
	TextComponent* textObj;
	MenuComponent* textObjProp;

};

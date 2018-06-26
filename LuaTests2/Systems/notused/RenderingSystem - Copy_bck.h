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


	void addEntity(Entity* e);
	std::list<Entity*> getEntities() const{ return EntityList; };
	void setEntities ( std::list<Entity*> Entities, std::string type );

	void Reset();
	void countdown ();

	Window* getWindow () const { return WSYS; };

	bool Check_resize ();
		

	std::string entityType; // Menu/Level/OBJ
private:
	std::list<Entity*> EntityList;
	
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

	std::string selector;
private:
	GraphicsComponent* Obj;
	TextComponent* textObj;
	MenuComponent* textObjProp;

};

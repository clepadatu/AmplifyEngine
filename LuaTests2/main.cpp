#include <iostream>
#include <string>
#include "Systems\MainSystem.h"

template <typename T>
// Create a component for entity <e>, and pass array of attributes in the form of <componentTable> (non-flat data)
void addComponent ( Entity* e, luabridge::LuaRef& componentTable )
	{
	e->addComponent ( std::type_index ( typeid(T) ), new T ( componentTable ) );
	}
//--------------------------------------

// Create a new entity and read all of its components. For each defined component, create this component and pass the array of attributes corresponding to it
Entity* loadEntity ( lua_State* L,const std::string& nodeName, const std::string& type, const int UID, const int UID_MARK )
	{
	using namespace luabridge;
	auto e = new Entity ( UID, UID_MARK );
	e->setType ( type );
	auto v = luah::getTableKeys(L, nodeName);
	
	LuaRef entityTable = getGlobal(L, nodeName.c_str());
	for ( auto& componentName : v )
		{
		if ( componentName == "GraphicsComponent" )
			{
			LuaRef gcTable = entityTable ["GraphicsComponent"];
			addComponent<GraphicsComponent> ( e, gcTable );
			}
		else if ( componentName == "NpcComponent" )
			{
			LuaRef npccTable = entityTable ["NpcComponent"];
			addComponent<NpcComponent> ( e, npccTable );
			}
		else if ( componentName == "LevelComponent" )
			{
			LuaRef lcTable = entityTable ["LevelComponent"];
			addComponent<LevelComponent> ( e, lcTable );
			}
		else if ( componentName == "MenuComponent" )
			{			
			LuaRef mTable= entityTable ["MenuComponent"];
			addComponent<MenuComponent> ( e, mTable );
			}
		else if ( componentName == "TextComponent" )
			{
			LuaRef tTable = entityTable ["TextComponent"];
			addComponent<TextComponent>(e, tTable);
			}
		else if (componentName == "UIComponent")
			{
			LuaRef uiTable = entityTable["UIComponent"];
			addComponent<UIComponent>(e, uiTable);
			addComponent<TextComponent>(e,uiTable);
			}

		std::cout << "Added " << componentName << " to [" << type << "]" << nodeName<< std::endl;
		}
	//std::cout << type << " UniqueID=" << e->GetUID ( ) << std::endl;
	return e;
	}
//--------------------------------------


//template <typename T>
//// Create a component for entity <e>, and pass array of attributes in the form of script. (Flat data)
//void addMenuComponent ( Entity* e, LuaScript script)
//	{
//	e->addComponent ( std::type_index ( typeid(T) ),new T(script) );
//	}
////--------------------------------------
//
//// Pass in type as <filename>, UID as ID declared in script, UID_MARK as random number.
//// This will create a MenuComponent and TextComponent, which are needed in order to have a menu structure printable to screen
//Entity* loadMenuEntity(const std::string& nodeName, const std::string& type, const int UID, const int UID_MARK)
//	{
//	using namespace luabridge;
//	auto e = new Entity ( UID, UID_MARK );
//	e->setType ( type );
//	LuaScript script("Scripts/UI/" + nodeName + ".lua");
//	addMenuComponent<MenuComponent> ( e,script );
//	addMenuComponent<TextComponent> ( e,script );
//	
//
//	std::cout <<"Added Menu/Text Component to ["<< type<<"]"<< nodeName << std::endl;
//	return e;
//	}
////--------------------------------------


int main ( )
	{
	//Real Made Engine - RM Engine - RME - AmplifyEngine
	// 
	auto AmplifyEngine = new MainSystem ();	

	AmplifyEngine->fireUpTheEngine ( );	
	AmplifyEngine->Inception ( );

	}
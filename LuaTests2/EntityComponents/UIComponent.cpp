#include "UIComponent.h"
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"
#include <iostream>

UIComponent::UIComponent(luabridge::LuaRef& componentTable)
	{
		using namespace luabridge;
		auto _name = componentTable["Name"];
		auto _display = componentTable["Display"];
		Name = _name.cast<std::string>();
		ID = componentTable["ID"];
		ID_minRange = componentTable["ID_minRange"];
		ID_maxRange = componentTable["ID_maxRange"];
		DisplayName = _display.cast<std::string>();
		Xposition = componentTable["Xposition"];
		Yposition = componentTable["Yposition"];
		PercentPositioning = componentTable["PercentPositioning"];
	}

#pragma once

#include <string>
#include "Component.h"
#include <map>
#include <vector>
#include <list>
#include "LuaHelperFunctions.h"

class UIComponent : public Component
	{
	public:
		UIComponent(LuaScript script);

		std::string Name;
		int ID;
		int ID_minRange;
		int ID_maxRange;
		std::string DisplayName;
		int Xposition;
		int Yposition;
		bool PercentPositioning;
	private:
		 
	};
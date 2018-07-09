#pragma once

#include <string>
#include "Component.h"
#include <map>
#include <vector>
#include <list>
#include "LuaHelperFunctions.h"

class MenuComponent : public Component
	{
	public:
		MenuComponent ( LuaScript script );

		std::string getName () const
			{
			return thisMenu.Name;
			}

		struct Item{
			public:
				std::string Name;
				int position_x;
				int position_y;
				int ID;
		};

		struct Menu{
			public:
				int ID;
				std::string Name;
				std::map<int,Item> Options;
		};
		
		
		void incrementActiveItem();
		void decrementActiveItem();
		void normalizeOptionID();

		int returnOptionID()  { return optionID; };
		void printOptions();

		std::map<int,Item> returnAllOptionItems();
		int ActiveSelectionID();


		bool Active=false;
		int optionID = 0;
		int ID;
		bool selection;
		Menu thisMenu;
		std::string NA = "Sorry, this menu is unavailable right now...";
		std::string Misc;
		
	private:
		int Timeout_enable;
		int Timeout;
	};
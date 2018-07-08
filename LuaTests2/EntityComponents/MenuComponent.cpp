#include "MenuComponent.h"
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"
#include <iostream>

MenuComponent::MenuComponent ( LuaScript script )
	{


	auto mID = script.get<int> ( "ID" );
	auto mName = script.get < std::string> ( "Name" );
	std::vector<std::string> Ovec = script.getStringVector("Optionvec");
	auto temp = Ovec [0];
	auto Xvec = script.getIntVector ( "Xvec" );
	auto Yvec = script.getIntVector ( "Yvec" );
	auto IDvec = script.getIntVector("IDvec");
	auto touten = script.get<int> ( "Timeout_enable" );
	auto tout = script.get<int> ( "Timeout" );
	auto act = script.get<int> ( "Active" );
	auto _misc = script.get<std::string> ( "MiscPhrase" );
	
	std::map<int,Item> OptionsMap;
	
	for ( int i = 0; i < Ovec.size ( ); ++i )
		{
		std::string n = Ovec [i];
		int x = Xvec [i];
		int y = Yvec [i];
		int iId = IDvec[i];
		Item MenuOptions = {
			n, x, y, iId
		};
		MenuOptions.Name = n;
		MenuOptions.position_x = x;
		MenuOptions.position_y = y;
		MenuOptions.ID = iId;

		OptionsMap.insert(std::pair<int,Item>(i,MenuOptions));		
		}
	
	thisMenu.Name = mName;
	thisMenu.ID = mID;
	thisMenu.Options = OptionsMap;

	Timeout_enable = touten;
	Timeout = tout;
	Active = act;
	Misc = _misc;
	std::cout << Misc << std::endl;
	}

void MenuComponent::incrementActiveItem()
{
	optionID += 1;
	normalizeOptionID();
}

void MenuComponent::decrementActiveItem()
{
	optionID -= 1;
	normalizeOptionID();
}

void MenuComponent::normalizeOptionID()
{
	//std::cout << "OptionID=" << optionID << std::endl;
	if (optionID == thisMenu.Options.size())
	{
		optionID = 0;
	}
	if (optionID < 0)
	{
		optionID = thisMenu.Options.size()-1;
	}
	//std::cout << "OptionID=" << optionID << std::endl;
}

std::map<int,MenuComponent::Item> MenuComponent::returnAllOptionItems()
{
	return thisMenu.Options;
}

int MenuComponent::ActiveSelectionID()
{
	return thisMenu.Options[optionID].ID;
}

void MenuComponent::printOptions()
{
	std::cout << "ID=" << thisMenu.ID << std::endl;
	//std::cout << "Here" << std::endl;
	/*std::list<MenuComponent::Item>::iterator it;
	for (it = thisMenu.Options.begin(); it != thisMenu.Options.end(); ++it){
		std::cout << it->Name;
	}*/
for ( auto  iter : thisMenu.Options )
	{
	std::cout << iter.first << std::endl;
	Item j = iter.second;
	std::cout << j.Name<<std::endl;

	}
		

}

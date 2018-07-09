#include "MenuComponent.h"
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"
#include <iostream>
#include <unordered_map>
std::unordered_map<std::string, luabridge::LuaRef> MenuComponent::getKeyValueMap(const luabridge::LuaRef& table)
{
	using namespace luabridge;
	std::unordered_map<std::string, LuaRef> result;
	if (table.isNil()) { return result; }

	auto L = table.state();
	push(L, table); // push table

	lua_pushnil(L);  // push nil, so lua_next removes it from stack and puts (k, v) on stack
	while (lua_next(L, -2) != 0) { // -2, because we have table at -1
		if (lua_isstring(L, -2)) { // only store stuff with string keys
			result.emplace(lua_tostring(L, -2), LuaRef::fromStack(L, -1));
		}
		lua_pop(L, 1); // remove value, keep key for lua_next
	}

	lua_pop(L, 1); // pop table
	return result;
}
MenuComponent::MenuComponent(luabridge::LuaRef& componentTable)
	{


	auto mID = componentTable["ID" ];
	auto mName = componentTable["Name"].cast< std::string> ( );
	std::cout << componentTable["Optionvec"].cast<std::string>() << std::endl;
	for (auto& pair : getKeyValueMap(componentTable)) {
		auto& key = pair.first;
		auto& value = pair.second;
		
		std::cout << key << "->" << value << std::endl;
	}
	std::vector<std::string> Ovec = componentTable["Optionvec"].cast<std::vector<std::string>>();
	auto temp = Ovec [0];
	auto Xvec = componentTable["Xvec"].cast<std::vector<int>>();
	auto Yvec = componentTable["Yvec"].cast<std::vector<int>>();
	auto IDvec = componentTable["IDvec"].cast<std::vector<int>>();
	auto touten = componentTable["Timeout_enable"].cast<int> ( );
	auto tout = componentTable["Timeout"].cast<int>();
	auto act = componentTable["Active"].cast<int>();
	auto _misc = componentTable["Timeout_enable"].cast<std::string>();
	
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

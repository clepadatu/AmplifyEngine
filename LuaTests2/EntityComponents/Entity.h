#pragma once

#include <map>
#include <string>
#include <typeindex>

class Component;

class Entity
	{
	public:
		Entity(const int UID, const int UID_MARK);
		~Entity ( );
		
		//add Component to Entity
		void addComponent ( std::type_index type, Component* c );
		void addComponent ( std::type_index type);

		//return certain Component type of this Entity; nullptr if not found;
		template <typename T>
		T* get ( )
			{
			auto it = components.find ( std::type_index ( typeid(T) ) );
			if ( it != components.end ( ) )
				{
				return dynamic_cast<T*>(it->second);
				}
			return nullptr;
			}


		void setType ( const std::string& type )
			{
			this->type = type;
			}

		std::string getType ( ) const
			{
			return type;
			}
		void SetUID(const int UID)
			{
			this->UID = UID;
			}
		int GetUID() const
		{
			return UID;
		}



	public:
		int UID;
		bool Active=false;
	private:

		std::string type;
		std::map<std::type_index, Component*> components;
	};
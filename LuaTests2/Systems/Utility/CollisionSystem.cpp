#include "CollisionSystem.h"

CollisionSystem::CollisionSystem ( )
	{
	
	}

void CollisionSystem::linkWithInterface(Window* windowInterface)
{
	this->windowInterface = windowInterface;
}

void CollisionSystem::DoCollision ( std::list<Entity*> &OBJ, std::list<Entity*> &PROJ ) // AABB - AABB collision
	{
	// Collision x-axis?
	for ( auto&i : PROJ )
		{
		if ( (*i).get<GraphicsComponent> ()->active == true )
			{
			/*if ( (*i).get<GraphicsComponent> ( )->_Should_draw ( windowInterface ) )
			(*i).get<GraphicsComponent> ( )->update_projectile ( );*/
			for ( auto&k : OBJ )
				{
				if ( (*k).get<GraphicsComponent> ()->destroyed == false )
					{
					
					if ( CheckCollision ( k,i) )
						{
						std::cout << "Collided" << std::endl;
						(*i).get<GraphicsComponent> ()->active = false;
						(*k).get<GraphicsComponent> ()->destroyed = true;
						}
					}
				}

			}

		}

	}

GLboolean CollisionSystem::CheckCollision ( Entity* one, Entity* two )
	{
	
	bool collisionX = one->get<GraphicsComponent> ( )->position.x + one->get<GraphicsComponent> ( )->Object_controls.return_size_x ( ) / (windowInterface->getWidth ( ) / 2) >= two->get<GraphicsComponent> ( )->projectile_position.x &&
		two->get<GraphicsComponent> ( )->projectile_position.x + two->get<GraphicsComponent> ( )->Object_controls.return_size_x ( ) / (windowInterface->getWidth ( ) / 2) >= one->get<GraphicsComponent> ( )->position.x;
	//std::cout << collisionX;
	// Collision y-axis?
	bool collisionY = one->get<GraphicsComponent> ( )->position.y + one->get<GraphicsComponent> ( )->Object_controls.return_size_y ( ) / (windowInterface->getHeight ( ) / 2) <= two->get<GraphicsComponent> ( )->projectile_position.y &&
		two->get<GraphicsComponent> ( )->projectile_position.y + two->get<GraphicsComponent> ( )->Object_controls.return_size_y ( ) / (windowInterface->getHeight ( ) / 2) >= one->get<GraphicsComponent> ( )->position.y;
	//std::cout << collisionY;
	// Collision only if on both axes
	return collisionX && collisionY;
	}
#include "MovementSystem.h"


/*Controls_MP::Controls_MP(int	width, int		height, int		type, double x, double y) : _width(width), _height(height), _type(type), mouse_x_last(x), mouse_y_last(y)
{
ProjectionMatrix	=	glm::ortho	(0.0f,	float(_width),	float(_height),	0.0f,	-1.0f,	1.0f); // In world coordinates, left,right,bottom,top,near,far
TranslationMatrix	=	glm::translate	(glm::mat4(1.0f),	glm::vec3(xpos,ypos,0.0f));
ModelMatrix		=	    glm::scale	(TranslationMatrix,		glm::vec3(60.0f, 60.0f,60.0f));

//maybe



}*/
MovementSystem::MovementSystem ( ) {};
MovementSystem::~MovementSystem ( ) {};

//INIT MVP Matrices
void MovementSystem::initMVP ( int	width, int		height, int		type)
	{
	ProjectionMatrix = glm::ortho(0.0f, float(width), float(height), 0.0f, 1.0f, -1.0f); // In world coordinates, left,right,bottom,top,near,far
	TranslationMatrix = glm::translate ( glm::mat4 ( 1.0f ), glm::vec3 ( xpos, ypos, 0.0f ) );
	ModelMatrix = glm::scale ( TranslationMatrix, glm::vec3 ( 60.0f, 60.0f, 60.0f ) );

	}

void MovementSystem::initMVP_text ( int	width, int		height, int		type)
	{
	ProjectionMatrix = glm::ortho(0.0f, float(width), float(height), 0.0f); // In world coordinates, left,right,bottom,top,near,far
	TranslationMatrix = glm::mat4 ( );
	ModelMatrix = glm::mat4 ( );
	}

void MovementSystem::initMVP_position ( int	width, int		height, int		type, float position_x, float position_y )
	{
	ProjectionMatrix = glm::ortho(0.0f, float(width), float(height), 0.0f, 1.0f, -1.0f); // In world coordinates, left,right,bottom,top,near,far
	TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position_x, position_y, 0.0f));
	ModelMatrix = glm::scale ( TranslationMatrix, glm::vec3 ( 90.0f, 90.0f, 90.0f ) );
	};
void MovementSystem::initMVP_position_size ( int	width, int		height, int		type, float position_x, float position_y, float size_x, float size_y, float size_z )
	{
	size_obj_x=size_x;
	size_obj_y = size_y;
	ProjectionMatrix = glm::ortho(0.0f, float(width), float(height), 0.0f, 1.0f, -1.0f); // In world coordinates, left,right,bottom,top,near,far
	TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position_x, position_y, 0.0f));
	ModelMatrix = glm::scale ( TranslationMatrix, glm::vec3 ( size_x, size_y, size_z ) );
	};





glm::mat4 MovementSystem::getMVP ( )
	{
	MVP_projectile = ProjectionMatrix*ViewMatrix*ModelMatrix;
	return glm::mat4 ( 1.0 );
	}


glm::mat4 MovementSystem::getProjectionMatrix ( )
	{
	return	ProjectionMatrix;
	}
glm::mat4 MovementSystem::getViewMatrix ( )
	{
	return	ViewMatrix;
	}
glm::mat4 MovementSystem::getModelMatrix ( )
	{
	return	ModelMatrix;
	}


float MovementSystem::getPlayerX ( )
	{
	TempMatrix = ProjectionMatrix*ViewMatrix*ModelMatrix;
	return TempMatrix [3][0];

	}
;
float MovementSystem::getPlayerY ( )
	{
	TempMatrix = ProjectionMatrix*ViewMatrix*ModelMatrix;
	return TempMatrix [3][1];
	};

void MovementSystem::computeMatrices ( )
	{
	//ModelMatrix = obj_move*ModelMatrix;
	}

float MovementSystem::return_obj_x ( )
	{
	glm::mat4 Temp = ProjectionMatrix*ViewMatrix*ModelMatrix;
	return Temp [3][0];
	}
float MovementSystem::return_obj_y ( )
	{
	glm::mat4 Temp = ProjectionMatrix*ViewMatrix*ModelMatrix;
	return Temp [3][1];
	}



float MovementSystem::return_size_x ( )
	{
	return size_obj_x;
	}
float MovementSystem::return_size_y ( )
	{
	return size_obj_y;
	}
float MovementSystem::return_size_z ( )
	{
	return size_obj_z;
	}





void MovementSystem::computeAIMovement()
	{
	//double currentTime = glfwGetTime ( );
	//float deltaTime = float ( currentTime - lastTime );
	TempMatrix = ProjectionMatrix*ViewMatrix*ModelMatrix;
	xpos = TempMatrix [3][0];
	ypos = TempMatrix [3][1];

	if ( intermediate == 0.0f )
		{
		ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( -0.005f, 0, 0 ) );

		intermediate = 1.0f;
		}

	if ( intermediate == 1.0f )
		{
		ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( -0.005f, 0, 0 ) );

		TempMatrix = ProjectionMatrix*ViewMatrix*ModelMatrix;
		xpos = TempMatrix [3][0];
		if ( xpos < -0.8f )
			intermediate = 2.0f;
		}

	if ( intermediate == 2.0f )
		{
		ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( +0.005f, 0, 0 ) );
		TempMatrix = ProjectionMatrix*ViewMatrix*ModelMatrix;
		xpos = TempMatrix [3][0];
		if ( xpos > 0.8f )
			intermediate = 1.0f;
		}

	//lastTime = currentTime;


	}
void MovementSystem::projectile_move ( float x, float y )
	{
	MVP_projectile [3][0] = x;
	MVP_projectile [3][1] = y;
	}


void MovementSystem::computeMatricesFromInputs ( int X, int Y, double mX, double mY )
	{
	if ( mouse_x_last == 0 && mouse_y_last == 0 )
		{
		mouse_x_last = mX;
		mouse_y_last = mY;
		}
	if ( mouse_x_last != mX && mouse_y_last != mY )
				{
				TranslationMatrix = glm::translate ( glm::mat4 ( 1.0f ), glm::vec3 ( mX, mY, 0.0f ) );
				ModelMatrix = glm::scale ( TranslationMatrix, glm::vec3 ( 30.0f, 30.0f, 30.0f ) );
				mouse_x_last = X;
				mouse_y_last = Y;
				}

	switch ( X )
		{
			case -1:
				ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( -speed, 0, 0 ) );
				break;
			case 1:
				ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( speed, 0, 0 ) );
				break;
			default:
				break;
		}
	switch ( Y )
		{
			case -1:
				ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( 0, speed, 0 ) );
				break;
			case 1:
				ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( 0, -speed, 0 ) );
				break;
			default:
				break;
		}

	}


//void MovementSystem::computeMatricesFromInputs ( Window* win, double x, double y )
//	{
//
//
//	//win->getMousePosition(x, y); maybe
//	if ( mouse_x_last != x && mouse_y_last != y )
//		{
//		TranslationMatrix = glm::translate ( glm::mat4 ( 1.0f ), glm::vec3 ( x, y, 0.0f ) );
//		ModelMatrix = glm::scale ( TranslationMatrix, glm::vec3 ( 60.0f, 60.0f, 60.0f ) );
//		mouse_x_last = x;
//		mouse_y_last = y;
//		}
//
//
//
//	double currentTime = glfwGetTime ( );
//	float deltaTime = float ( currentTime - lastTime );
//	TempMatrix = ProjectionMatrix*ViewMatrix*ModelMatrix;
//	xpos = TempMatrix [3][0];
//	ypos = TempMatrix [3][1];
//
//
//	//Aleft - move cube axis x
//	if ( win->isKeyPressed ( 263 ) && xpos>-1.0f )
//		{
//
//
//		//camera += glm::vec3(0, speed*deltaTime, speed*deltaTime);
//		//rotation command
//		//ModelMatrix = glm::rotate(ModelMatrix, speed*deltaTime, glm::vec3(0, 0, -1));
//
//		std::cout << "Current Xposition is: " << xpos << std::endl;
//		ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( -speed*deltaTime, 0, 0 ) );
//
//		}
//	//Aright - Move cube axis x
//	if ( win->isKeyPressed ( 262 ) && xpos<1.0f )
//		{
//
//
//		//camera -= glm::vec3(0, speed*deltaTime, speed*deltaTime);
//		//rotation command
//		//ModelMatrix = glm::rotate(ModelMatrix, speed*deltaTime, glm::vec3(0, 0, 1));
//
//		std::cout << "Current Xposition is: " << xpos << std::endl;
//		ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( speed*deltaTime, 0, 0 ) );
//
//		}
//
//
//	//Adown - Move cube axis x
//	if ( win->isKeyPressed ( 264 ) && ypos>-1 )
//		{
//
//
//		//camera -= glm::vec3(0, speed*deltaTime, speed*deltaTime);
//		//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-speed*deltaTime, 0, 0));
//		std::cout << "Current Yposition is: " << ypos << std::endl;
//		ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( 0, speed*deltaTime, 0 ) );
//		}
//
//	//Aup - Move cube axis x
//	if ( win->isKeyPressed ( 265 ) && ypos<1 )
//		{
//
//
//		//camera -= glm::vec3(0, speed*deltaTime, speed*deltaTime);
//		//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(speed*deltaTime, 0, 0));
//		std::cout << "Current Yposition is: " << ypos << std::endl;
//		ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( 0, -speed*deltaTime, 0 ) );
//		}
//
//	if ( win->isKeyPressed ( 32 ) )
//		{
//		space_pressed = 1;
//		}
//
//	if ( space_pressed == 1 )
//		{
//		//std::cout << "Current Yposition is: " << ypos << std::endl;
//		ModelMatrix = glm::translate ( ModelMatrix, glm::vec3 ( 0, -speed*deltaTime, 0 ) );
//		}
//
//	if ( win->isKeyPressed ( 256 ) )
//		{
//		space_pressed = 0;
//		}
//
//
//
//	computeMatrices ( );
//
//	lastTime = currentTime;
//
//	}

//bool MovementSystem::check_click ( Window* win )
//	{
//	if ( win->isMouseButtonPressed ( GLFW_MOUSE_BUTTON_LEFT ) )
//		return true;
//	else
//		return false;
//	}


/*if (x != _x && y != _y)
{
ModelMatrix = glm::translate(ModelMatrix, glm::vec3(float((x - _x) / 100), float((y - _y) / 100), 0.0f));
_x = x;
_y = y;
}*/
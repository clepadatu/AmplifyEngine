#include "GraphicsComponent.h"
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"
#include <iostream>

GraphicsComponent::GraphicsComponent ( luabridge::LuaRef& componentTable )
	{

	
	using namespace luabridge;
	auto filenameRef = componentTable ["filename"];
	if ( filenameRef.isString ( ) )
		{
		filename = filenameRef.cast<std::string> ( );
		}
	else
		{
		std::cout << "Error, GraphicsComponent.filename is not a string!" << std::endl;
		}

	size_x = componentTable["size_x"];
	size_y = componentTable ["size_y"];
	position_x = componentTable ["position_x"];
	position_y = componentTable ["position_y"];

	initBufferData ();
	
	}


void GraphicsComponent::initBufferData ()
	{
	GLfloat vertices_coordinates [] =
		{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f

		};
	GLushort indices_map [] =
		{
		0, 1, 2,
		2, 0, 3
		}; //bottom
	GLfloat texture_coordinates [] =
		{
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
		};
	GLfloat colors []=
		{
		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
		};
	Object_ibo.set_properties ( indices_map, 6 );
	Object.addBuffer ( new Buffer ( vertices_coordinates, 4 * 3, 3 ), 0 );
	Object.addBuffer ( new Buffer ( colors, 4 * 4, 4 ), 1 );
	Object.addBuffer ( new Buffer ( texture_coordinates, 4 * 2, 2 ), 2 );

	//Texture loading
	glGenTextures ( 1, &O_texture );
	glBindTexture ( GL_TEXTURE_2D, O_texture );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const char *cstr = filename.c_str();
	unsigned char* image = SOIL_load_image ( cstr, &O_texture_width, &O_texture_height, 0, SOIL_LOAD_RGBA );
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, O_texture_width, O_texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	glGenerateMipmap ( GL_TEXTURE_2D );
	SOIL_free_image_data ( image );
	glBindTexture ( GL_TEXTURE_2D, 0 );
		
	}
void GraphicsComponent::enableShaderonly ( )
	{
	
	Object_shader.enable ( );
	}
void GraphicsComponent::enableShader ()
	{
	Object_shader.Initialise_shader ( "Extras/shaders/basic.vert", "Extras/shaders/basic.frag" );
	Object_shader.enable ();
	}

void GraphicsComponent::computeMatrices ( )
	{
	glm::mat4 MVP = Object_controls.getProjectionMatrix ( ) * Object_controls.getViewMatrix ( )*Object_controls.getModelMatrix ( );
	glUniformMatrix4fv ( Object_shader.getUniformLocation ( "MVP" ), 1, GL_FALSE, &MVP [0][0] );
	}
void GraphicsComponent::computeAIMovement()
{
	Object_controls.computeAIMovement();
	position = glm::vec2 ( Object_controls.return_obj_x ( ), Object_controls.return_obj_y ( ) );
}

void GraphicsComponent::bind ( )
	{

	Object.bind ( );
	Object_ibo.bind ( );

	};
void GraphicsComponent::unbind ( )
	{
	Object_ibo.unbind ( );
	Object.unbind ( );
	};

void GraphicsComponent::texture_activate ( )
	{
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, O_texture );
	glUniform1i ( Object_shader.getUniformLocation ( "Ship_texture" ), 0 );
	};

void GraphicsComponent::Draw ( )
	{
	glDrawElements ( GL_TRIANGLES, ibo_count ( ), GL_UNSIGNED_SHORT, (void*) 0 );
	}

GLuint GraphicsComponent::ibo_count ( )
	{
	return Object_ibo.getCount ( );
	};

void GraphicsComponent::Initialise_controls ( int window_width, int window_height, int type, float position_x, float position_y )
	{
	
	Object_controls.initMVP_position_size(window_width, window_height, type, position_x, position_y, size_x, size_y, 30.0f);
	}

void GraphicsComponent::PlayerUpdate(bool resized, int X, int Y, Window* Win, double mouse_x, double mouse_y)
	{
	if ( resized )
		Initialise_controls ( Win->getWidth ( ), Win->getHeight ( ), 1, rand ( ) % Win->getWidth ( ), rand ( ) % (Win->getHeight ( ) / 3) + 60 );
	//Win->getMousePosition (mouse_x,mouse_y);
	//Main_window->getMousePosition ( mouse_x, mouse_y );
	//std::cout << "(X,Y)   =   " << mouse_x << "," << mouse_y << std::endl;
	Object_controls.computeMatricesFromInputs (X,Y,mouse_x,mouse_y );
	}

glm::vec2 GraphicsComponent::playerGetFacingDirection ()
	{
	float origin_x = Object_controls.getPlayerX ( );
	float origin_y = Object_controls.getPlayerY ( );
	glm::vec2 projectile_direction = glm::vec2 ( origin_x, 1.0f ) - glm::vec2 ( origin_x, origin_y );
	projectile_direction = glm::normalize ( projectile_direction );
	return projectile_direction;
	}

glm::vec2 GraphicsComponent::playerGetPosition ()
	{
	float origin_x = Object_controls.getPlayerX ( );
	float origin_y = Object_controls.getPlayerY ( );
	return glm::vec2 ( origin_x, origin_y );
	}







void GraphicsComponent::setupProjectile ( glm::vec2 pos, glm::vec2 dir, float speed)
	{
	projectile_position = pos;
	projectile_direction = dir;
	projectile_speed = speed;
	
	
	active = false;
	steps = 0;


	}

void GraphicsComponent::Reinit_pos ( glm::vec2 pos )
	{
	projectile_position = pos;
	}

bool GraphicsComponent::_Should_draw (Window* Win )
	{
	if ( active == false )
		{
		//active = false;
		
		this->Reinit_pos ( glm::vec2 ( Win->getWidth(), Win->getHeight()) );
		//std::cout << this->PID << " is done executing, because liftime=" << projectile_lifetime << std::endl;
		return false;
		};
	//std::cout << "alive" << std::endl;
	return true;

	}

void GraphicsComponent::moveProjectile ()
	{
	for ( int times = 0; times < steps; times++ )
		{
		this->update_projectile ();
		steps--;
		}
	}

void GraphicsComponent::update_projectile ( )
	{
	projectile_position += projectile_direction*projectile_speed;
	if ( projectile_position.y > 1 )
		{
		active = false;
		}
	}

void GraphicsComponent::projectileComputeMatrices ( )
	{
	//this->update_projectile ( );
	glm::mat4 MVP = Object_controls.getProjectionMatrix ( ) * Object_controls.getViewMatrix ( )*Object_controls.getModelMatrix ( );
	//std::cout << "Projectile id=" << this->PID << ", moved to (x,y)=" << projectile_position.x << "," << projectile_position.y << std::endl;
	MVP [3][0] = projectile_position.x;
	MVP [3][1] = projectile_position.y;
	glUniformMatrix4fv ( Object_shader.getUniformLocation ( "MVP" ), 1, GL_FALSE, &MVP [0][0] );
	}
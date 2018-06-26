#pragma once

#include <string>
#include "Component.h"
#include <GL/glew.h>
#include <SOIL.h>
#include "../Extras/buffers/buffer.h"
#include "../Extras/buffers/indexbuffer.h"
#include "../Extras/buffers/vertexarray.h"
#include "../Extras/buffers/shader.h"
#include	<glm.hpp>
#include	<gtc/matrix_transform.hpp>
#include	<gtx/transform.hpp>
#include "../Systems/Utility/MovementSystem.h"
#include "../Extras/window/window.h"


class GraphicsComponent : public Component
	{
	public:
		void initBufferData ();
		void enableShader ();
		void enableShaderonly ( );
		void Initialise_controls(int window_width, int window_height, int type, float position_x, float position_y);
		void computeMatrices ( );
		void computeAIMovement();
		void bind ();
		void unbind ();
		void texture_activate ();
		void Draw ();
		GLuint ibo_count ();

		void PlayerUpdate(bool resized, int X, int Y, Window* Win, double mouse_x, double mouse_y);
		

		GraphicsComponent ( luabridge::LuaRef& componentTable );

		void setFilename ( const std::string& filename )
			{
			this->filename = filename;
			}

		std::string getFilename ( ) const
			{
			return filename;
			}
		
		void setScreenData(const int width, const int height)
		{
			this->screen_width = width;
			this->screen_height = height;
		}

		int position_x;
		int position_y;
		bool destroyed = false;
		glm::vec2 position;
	private:
		std::string filename;
	
		float size_x;
		float size_y;

		int screen_width;
		int screen_height;
		


		//hardcoded for now
		GLfloat vertices_coordinates [12];		
		GLushort indices_map [6];
		GLfloat texture_coordinates [8];
		GLfloat colors [16];
		
		VertexArray Object;
		IndexBuffer Object_ibo;
		Shader Object_shader;
	public:
		MovementSystem Object_controls;
	private:

		GLuint O_texture;
		int O_texture_width;
		int O_texture_height;

	

		//Projectile ?
	private:
		float projectile_speed;
		glm::vec2 projectile_direction;

	public:
		glm::vec2 projectile_position;
		bool active;
		int steps;

		void update_projectile ( );



		glm::vec2 playerGetFacingDirection ( );
		glm::vec2 playerGetPosition ();

		void Initialise_controls ( );
		void Initialise_texture ( );
		void projectileComputeMatrices ( );
		void _To_screen ( );
		bool _Should_draw ( Window* Win );
		void moveProjectile ();
		//Projectile ( glm::vec2 pos, glm::vec2 dir, float speed, int lifetime, double suid );
		//~Projectile ( );
		//????bool operator==(const Projectile& other);
		void Reinit_pos ( glm::vec2 pos );
		void Reset_to_mouse ( );

		void setupProjectile ( glm::vec2 pos, glm::vec2 dir, float speed);
	};
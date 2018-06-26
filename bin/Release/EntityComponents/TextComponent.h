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
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <G:\=====Repositories====\Amplify/Dependencies/GLM/include/gtc/type_ptr.hpp>
#include "LuaHelperFunctions.h"
class TextComponent : public Component
	{
	public:
		void initBufferData ( );
		void enableShader ( );
		void enableShaderonly ( );
		void Initialise_controls ( int window_width, int window_height, int type );				
		void bind ( );
		void unbind ( );		
		void Draw ( );
		GLuint ibo_count ( );

		TextComponent ( LuaScript script );
		
		void setScreenData ( const int width, const int height )
			{
			this->screen_width = width;
			this->screen_height = height;
			}

		void render_text ( std::string type, GLfloat scale, int x, int y, double value, std::string text, std::string color );

	private:
		void Init_FreeType();
		void Init_CharacterMap();
		void Compute_matrices();
		void To_screen();


	private:
		FT_Face face;
		FT_Library ft;
		FT_GlyphSlot g;

		struct Character
		{
			GLuint     TextureID;  // ID handle of the glyph texture
			glm::ivec2 Size;       // Size of glyph
			glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
			GLuint     Advance;    // Offset to advance to next glyph				
		};
		std::map<GLchar, Character> Characters;
		Buffer Object_buffer;
		GLfloat x;
		GLfloat y;


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
		MovementSystem Object_controls;
		vec3 colorvec;

		//*******************************Maybe reorganize***
	
		

		
	public:

	};
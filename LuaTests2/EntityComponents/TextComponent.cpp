#include "TextComponent.h"
#include "../../Dependencies/LuaBridge-master/Source/LuaBridge/LuaBridge.h"
#include <iostream>

TextComponent::TextComponent(luabridge::LuaRef& componentTable)
	{

	Init_FreeType ( );
	Init_CharacterMap ( );

	initBufferData ( );

	}


void TextComponent::initBufferData ( )
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
	GLfloat colors [] =
		{
		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
		};

	Object.addBuffer_text ( new Buffer ( NULL, 6 * 4, 4, 1 ), 0 );
	}

void TextComponent::enableShaderonly ( )
	{

	Object_shader.enable ( );
	}


void TextComponent::enableShader ( )
	{
	Object_shader.Initialise_shader ( "extras/shaders/FTtext.vert", "extras/shaders/FTtext.frag" );
	Object_shader.enable ( );
	}


void TextComponent::bind ( )
	{

	Object.bind ( );
	Object_ibo.bind ( );

	};
void TextComponent::unbind ( )
	{
	Object_ibo.unbind ( );
	Object.unbind ( );
	};



void TextComponent::Draw ( )
	{
	glDrawElements ( GL_TRIANGLES, ibo_count ( ), GL_UNSIGNED_SHORT, (void*) 0 );
	}

GLuint TextComponent::ibo_count ( )
	{
	return Object_ibo.getCount ( );
	};

void TextComponent::Initialise_controls ( int window_width, int window_height, int type)
	{

	Object_controls.initMVP_text ( window_width, window_height, type);
	}

void TextComponent::To_screen()
{
	this->Compute_matrices();
}

void TextComponent::Compute_matrices()
{
	glm::mat4 MVP = Object_controls.getProjectionMatrix();
	glUniformMatrix4fv(Object_shader.getUniformLocation("TextposM"), 1, GL_FALSE, glm::value_ptr(MVP));
}



void TextComponent::render_text ( std::string type, GLfloat scale, int x, int y, double value, std::string text, std::string color )
	{
	
	Object_shader.enable ( );
	if ( type == "FPS" || type == "Score" )
		{
		if ( value != NULL )
			{
			text = text + std::to_string ( value );
			}
		}
	if ( color == "red" )
		colorvec = vec3 ( 1.0f, 0.0f, 0.0f );
	else if ( color == "black" )
		colorvec = vec3 ( 0.0f, 0.0f, 0.0f );
	else if ( color == "green" )
		colorvec = vec3 ( 0.0f, 1.0f, 0.0f );
	else
	colorvec = vec3 ( 1.0f, 1.0f, 1.0f );

	
	To_screen ( );
	Object.bind ( );
	Object_shader.setUniform3f ( "textColor", colorvec );

	glActiveTexture ( GL_TEXTURE0 );


	std::string::const_iterator c;
	for ( c = text.begin ( ); c != text.end ( ); c++ )
		{
		Character ch = Characters [*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y + (this->Characters ['H'].Bearing.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices [6][4] = {
			{ xpos, ypos + h, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 0.0 },
			{ xpos, ypos, 0.0, 0.0 },

			{ xpos, ypos + h, 0.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 1.0 },
			{ xpos + w, ypos, 1.0, 0.0 }
			};
		// Render glyph texture over quad
		glBindTexture ( GL_TEXTURE_2D, ch.TextureID );
		// Update content of VBO memory
		Object.testbind ( );
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData ( GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices ); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer ( GL_ARRAY_BUFFER, 0 );
		// Render quad
		glDrawArrays ( GL_TRIANGLES, 0, 6 );
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

		}
	Object.testunbind ( );
	Object.unbind ( );


	}




void TextComponent::Init_FreeType ( )
	{
	if ( FT_Init_FreeType ( &ft ) )
		{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		}


	if ( FT_New_Face ( ft, "Extras/fonts/LucidaSansRegular.ttf", 0, &face ) )
		{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		}
	FT_Set_Pixel_Sizes ( face, 0, 48 );


	}

void TextComponent::Init_CharacterMap ( )
	{
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 ); // Disable byte-alignment restriction

	for ( GLubyte c = 0; c < 128; c++ )
		{
		// Load character glyph 
		if ( FT_Load_Char ( face, c, FT_LOAD_RENDER ) )
			{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
			}
		// Generate texture
		GLuint texture;
		glGenTextures ( 1, &texture );
		glBindTexture ( GL_TEXTURE_2D, texture );
		glTexImage2D (
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
			);
		// Set texture options
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2 ( face->glyph->bitmap.width, face->glyph->bitmap.rows ),
			glm::ivec2 ( face->glyph->bitmap_left, face->glyph->bitmap_top ),
			face->glyph->advance.x
			};
		Characters.insert ( std::pair<GLchar, Character> ( c, character ) );
		}
	FT_Done_Face ( face );
	FT_Done_FreeType ( ft );
	glBindTexture ( GL_TEXTURE_2D, 0 );
	}

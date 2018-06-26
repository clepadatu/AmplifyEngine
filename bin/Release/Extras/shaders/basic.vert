#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 Ship_texture_coordinates_vert;


/*uniform mat4 pr_matrix;
uniform mat4 vw_matrix;
uniform mat4 ml_matrix;*/



uniform vec3 color_change;
uniform mat4 MVP;
uniform mat4 rotate;


//
out DATA
{
vec3 color_change;
vec4 color;

} vs_out;
out vec2 Ship_texture_coordinates;

void main()
{
	
	gl_Position =MVP* vec4(position,1);
	//



	vs_out.color_change=color_change;
	vs_out.color=color;
	Ship_texture_coordinates= vec2(Ship_texture_coordinates_vert.x,Ship_texture_coordinates_vert.y);

	
}
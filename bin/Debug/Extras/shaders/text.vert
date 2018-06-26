#version 120

//attribute vec4 coord;
layout (location = 0) in vec3 position;
//varying vec2 texcoord;
layout (location = 2) in vec2 Ship_texture_coordinates_vert;
layout (location = 1) in vec4 color;



uniform vec3 color_change;
uniform mat4 MVP;
uniform mat4 rotate;
out DATA
{
vec3 color_change;
vec4 color;

} vs_out;
out vec2 Ship_texture_coordinates;



void main(void) {
  //gl_Position = vec4(coord.xy, 0, 1);
  	gl_Position =MVP* vec4(position,1);

  //texcoord = coord.zw;
	vs_out.color_change=color_change;
	vs_out.color=color;
	Ship_texture_coordinates= vec2(Ship_texture_coordinates_vert.x,Ship_texture_coordinates_vert.y);
}
#version 400 core

layout (location = 0) out vec4 color;

in vec2 Ship_texture_coordinates;
uniform sampler2D Ship_texture;


in DATA
{
vec3 color_change;
vec4 color;

} fs_in;
void main()
{


//color=fs_in.color;
color=texture(Ship_texture,Ship_texture_coordinates);

}
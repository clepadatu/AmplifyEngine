#version 120

//varying vec2 texcoord;
in vec2 Ship_texture_coordinates;

//uniform sampler2D tex;
uniform sampler2D Ship_texture;

//uniform vec4 color;
layout (location = 0) out vec4 color;

in DATA
{
vec3 color_change;
vec4 color;

} fs_in;

void main(void) {
  //gl_FragColor = vec4(1, 1, 1, texture2D(tex, texcoord).r) * color;
  color=texture(Ship_texture,Ship_texture_coordinates);
}
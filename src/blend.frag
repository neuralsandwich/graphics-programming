#version 400

// Texture 1
uniform sampler2D tex1;
// Texture 2
uniform sampler2D tex2;
// Texture used to blend tex1 and tex2
uniform sampler2D blend_map;

in vec2 vertex_tex_coord;
out vec4 col;

void main() {
  // Get colour from texture 1
  vec4 col1 = texture(tex1, vertex_tex_coord);
  // Get colour from texture 2
  vec4 col2 = texture(tex2, vertex_tex_coord);
  // Get blend value
  vec4 blend = texture(blend_map, vertex_tex_coord);
  // Mix the colours.  Use the a component from the blend value
  col = mix(col1, col2, blend.a);
}
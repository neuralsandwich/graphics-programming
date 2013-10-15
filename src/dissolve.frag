#version 400

uniform sampler2D tex;
uniform sampler2D dissolve_tex;
uniform float dissolve_factor;

in vec2 vertex_tex_coord;
out vec4 col;

void main() {
  // Get dissolve value from the alpha map
  vec4 dissolve_value = texture(dissolve_tex, vertex_tex_coord);
  
  // if alpha component is less than the dissolve factor, discard
  if (dissolve_value.a > dissolve_factor) {
	discard;
  }

  col = texture(tex, vertex_tex_coord);
}
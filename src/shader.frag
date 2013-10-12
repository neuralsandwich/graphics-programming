#version 400

// The texture to be used
uniform sampler2D tex;

// Incoming texture co-ordinate
in vec2 vertex_tex_coord;
// The outgoing colour for the pixel
out vec4 col;

void main ()
{
	// Sample the texture to get the pixel colour
	col = texture(tex, vertex_tex_coord);
}
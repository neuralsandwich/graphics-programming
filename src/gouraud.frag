#version 400

uniform sampler2D tex;

in vec2 vertex_tex_coord;		// Incoming texture coordinate
in vec4 primary_colour;			// Primary colour for fragment
in vec4 secondary_colour;		// Secondary colour for fragment

// Outgoing colour
out vec4 col;

void main() {

	// Sample texutre
	vec4 tex_colour = texture(tex, vertex_tex_coord);

	// Calculate final fragment colour
	col = (primary_colour  * tex_colour) + secondary_colour;
}
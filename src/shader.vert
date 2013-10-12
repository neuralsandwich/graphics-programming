#version 400

// Model-View-Projection matrix
uniform mat4 MVP;

// The vertex position in model space
layout (location = 0) in vec3 position;
// The vertex normal
layout (location = 2) in vec2 tex_coord;

// mOutput vertex colour
out vec2 vertex_tex_coord;

void main()
{
	// Set the position of vertex in screen space
	gl_Position = MVP * vec4(position, 1.0);

	// Outpput the texture co-ordinate to the fragment shader
	vertex_tex_coord = tex_coord;
}
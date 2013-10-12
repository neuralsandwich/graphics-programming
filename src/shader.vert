#version 400

// Model-View-Projection matrix
uniform mat4 MVP;
// The colour of our light
uniform vec4 colour;
// Additional color to add
uniform vec4 hue;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec4 vertex_colour;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	float s = max(dot(normalize(vec3(1.0, 0.5, 0.2)), normal), 0.0);
	vertex_colour = vec4(0.1, 0.1, 0.1, 1.0) + (s * colour * colour) + hue;
	vertex_colour.a = 1.0;
}
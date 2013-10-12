#version 400

in vec4 vertex_colour;
out vec4 col;

void main ()
{
	col = vertex_colour;
}
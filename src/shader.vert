#version 400

uniform mat4 MVP;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec4 colour;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	float s = max(dot(normalize(vec3(1.0, 0.5, 0.2)), normal), 0.0);
	colour = vec4(0.1, 0.1, 0.1, 1.0) + (s * vec4(1.0, 0.0, 0.0, 1.0) * vec4(1.0, 0.0, 0.0, 1.0));
	colour.a = 1.0;
}
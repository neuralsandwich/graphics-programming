#version 400

// Model-View-Projection matrix
uniform mat4 MVP;
// the ambient intensity in the scene
uniform vec4 ambient_intensity;
// the material colour of the object
uniform vec4 material_colour;


// The vertex position in model space
layout (location = 0) in vec3 position;

// Output vertex colour
out vec4 vertex_colour;

void main()
{
  // Transform position
  gl_Position = MVP * vec4(position, 1.0);
  // Calculate ambient component
  vec4 ambient = ambient_intensity * material_colour;
  vertex_colour = ambient;
}
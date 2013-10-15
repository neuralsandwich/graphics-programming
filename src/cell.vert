#version 400

// Model-View-Projection matrix
uniform mat4 MVP;

// The vertex position in model space
layout (location = 0) in vec3 position;
// The vertex normal
layout (location = 1) in vec3 normal;

// Output vertex colour
out float tex_coord;

void main()
{
  // Transform position
  gl_Position = MVP * vec4(position, 1.0);
  // Texture coordinate is a scalar based on angle between surface and light
  // Light direction
  vec3 light_dir = normalize(vec3(1.0, 1.0, 1.0));
  // Texture coordinate
  tex_coord = max(0.0, dot(normalize(normal), light_dir));
}
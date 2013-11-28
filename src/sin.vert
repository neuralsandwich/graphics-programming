#version 400

layout (location = 0) in vec3 position;		// The vertex position in model space
layout (location = 2) in vec2 tex_coord;	// Texture co-ordinate

// Output variables
out vec2 vertex_tex_coord;

void main()
{
  // Transform position
  gl_Position = vec4(position, 1.0);

  // Output tex coord
  vertex_tex_coord = tex_coord;
}
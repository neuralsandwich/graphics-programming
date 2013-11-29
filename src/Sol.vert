#version 400

uniform mat4 model;					
uniform mat4 MVP;					// Model-View-Projection matrix
uniform mat3 normal_matrix;			// Updated normals

layout (location = 0) in vec3 position;		// The vertex position in model space
layout (location = 1) in vec3 normal;		// Incoming normal
layout (location = 2) in vec2 tex_coord;	// Texture co-ordinate

const float FC = 1.0/log(1.0e8*1e-6 + 1);

// Output variables
out vec3 vertex_position;
out vec3 transformed_normal;
out vec2 vertex_tex_coord;
out float logz;


void main()
{
  // Past through position
  vertex_position = (model * vec4(position, 1)).xyz;

  // Transform position
  gl_Position = MVP * vec4(position, 1.0);
  
  // Updating normal with normal matrix
  transformed_normal = normal_matrix * normal;

  // Output tex coord
  vertex_tex_coord = tex_coord;

  // Using Logarithmic Depth to stop Z fighting on Earth atmosphere
  //gl_Position.z = log(1e-6 * gl_Position.z + 1) / log(1e-6 * 150e6 + 1) * gl_Position.w;
  logz = log(gl_Position.w*1e-6 + 1)*FC;
  gl_Position.z = (2*logz - 1)*gl_Position.w;
}
#version 400

uniform mat4 model;
uniform mat4 MV;
uniform mat4 MVP;					// Model-View-Projection matrix
uniform mat3 normal_matrix;			// Updated normals

uniform vec3 eye_position;
uniform vec3 direction;

layout (location = 0) in vec3 position;		// The vertex position in model space
layout (location = 1) in vec3 normal;		// Incoming normal
layout (location = 2) in vec2 tex_coord;	// Texture co-ordinate
layout (location = 4) in vec3 tangent;
layout (location = 5) in vec3 binormal;

// Output variables
out vec3 transformed_position;
out vec3 light_dir;
out vec3 view_dir;
out vec2 vertex_tex_coord;

void main()
{
  // Calculate screen position
  gl_Position = MVP * vec4(position, 1.0);

  // Updating normal with normal matrix
  transformed_position = (model * vec4(position, 1.0)).xyz;

  // Output tex coord
  vertex_tex_coord = tex_coord;

  // Calculate position in camera space
  vec3 pos = (MV * vec4(position, 1.0)).xyz;

  // Create transform matrix for view and light directions
  vec3 n = normalize(normal_matrix * normal);
  vec3 t = normalize(normal_matrix * tangent);
  vec3 b = normalize(normal_matrix * binormal);
  mat3 tbn_transform = mat3(
    t.x, b.x, n.x,
    t.y, b.y, n.y,
    t.z, b.z, n.z);

  view_dir = normalize(eye_position - pos);
  view_dir = tbn_transform * view_dir;
  light_dir = direction * tbn_transform;

  // Using Logarithmic Depth to stop Z fighting on Earth atmosphere
  gl_Position.z = log(1e-6 * gl_Position.z + 1) / log(1e-6 * 150e6 + 1) * gl_Position.w;
}
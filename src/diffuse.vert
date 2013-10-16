#version 400

// Model-View-Projection matrix
uniform mat4 MVP;
// Updated normals
uniform mat3 normal_matrix;
// the material colour of the object
uniform vec4 material_colour;
// Light colour
uniform vec4 light_colour;
// Direction of the light
uniform vec3 light_direction;

// The vertex position in model space
layout (location = 0) in vec3 position;

// Incoming normal
layout (location = 1) in vec3 normal;

// Output vertex colour
out vec4 vertex_colour;

void main()
{
  // Transform position
  gl_Position = MVP * vec4(position, 1.0);

  // Updating normal with normal matrix
  vec3 transformed_normal = normal * normal_matrix;

  // Calculate diffuse componenet
  // Calculate dot product
  float k = max(dot(transformed_normal, light_direction), 0.0);
  // Calculate diffuse light
  vec4 diffuse = k * (material_colour * light_colour);
  // Ensure ambient component is 1.0
  diffuse.a = 1.0;
  // Set output vertex colour
  vertex_colour = diffuse;
}
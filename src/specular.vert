#version 400

uniform mat4 MVP;					// Model-View-Projection matrix
uniform mat3 normal_matrix;			// Updated normals
uniform vec4 specular_material;		// the material of the object
uniform vec4 light_colour;			// Light colour
uniform vec3 light_direction;		// Direction of the light
uniform vec3 eye_position;			// Camera Position
uniform float shininess;			// Materials shininess factor


layout (location = 0) in vec3 position;		// The vertex position in model space
layout (location = 1) in vec3 normal;		// Incoming normal

// Output vertex colour
out vec4 vertex_colour;

void main()
{
  // Transform position
  gl_Position = MVP * vec4(position, 1.0);

  // Updating normal with normal matrix
  vec3 transformed_normal = normal_matrix * normal;

  // Calculate view direction
  vec3 view_direction = normalize(eye_position - position);

  vec3 half_vector = normalize(light_direction + view_direction);

  // Calculate specular componenet
  // Calculate specular intensity
  float s = pow(max(dot(transformed_normal, half_vector), 0.0), shininess);
  // Calculate specular light
  vec4 specular = (specular_material * light_colour) * s;
  // Ensure ambient component is 1.0
  specular.a = 1.0;
  // Set output vertex colour
  vertex_colour = specular;
}
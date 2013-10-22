#version 400

layout (std140) uniform;

uniform material
{
	vec4 emissive;             // Emissive light values
	vec4 diffuse_reflection;   // Diffuse reflection vector
	vec4 specular_reflection;  // Specular reflection vector
	float shininess;           // Materials shininess factor
} mat;

uniform directional_light
{
	vec4 ambient_intensity;    // Ambient intensity for scene
	vec4 colour;               // Light colour
	vec3 direction;            // Direction of the light
} light;

uniform vec3 eye_position;     // Camera position
uniform sampler2D tex;         // Texutre sample

in vec3 vertex_position;       // Model vertex transformed with world position
in vec3 transformed_normal;    // Model normal transformed with world matrix
in vec2 vertex_tex_coord;      // Incoming texture coordinate


// Outgoing colour
out vec4 col;

void main() {

	// Calculate ambient light
	vec4 ambient = mat.diffuse_reflection * light.ambient_intensity;

	// Calculate diffuse light
	vec4 diffuse = (mat.diffuse_reflection * light.colour) * max(dot(transformed_normal, light.direction), 0.0);

	// Calculate view direction
	vec3 view_direction = normalize(eye_position - vertex_position);

	// Calculate half_vector
	vec3 half_vector = normalize(light.direction + view_direction);

    /*
     * Calculate specular lighting
     *
     * Calculate specular intensity
     */
	vec4 specular = (mat.specular_reflection * light.colour) * pow(max(dot(transformed_normal, half_vector), 0.0), mat.shininess);


	// Sample texutre
	vec4 tex_colour = texture(tex, vertex_tex_coord);

	// Calculate final fragment colour
	col = ((mat.emissive + ambient + diffuse) * tex_colour) + specular;
	col.a = 1.0;
}
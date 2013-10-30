#version 400

layout (std140) uniform;

uniform material
{
	vec4 emissive;				// Emissive light values
	vec4 diffuse_reflection;	// Colour for diffuse light reflected from material 
	vec4 specular_reflection;   // Colour for specular light reflected from material 
	float shininess;             // Materials shininess factor
} mat;

uniform directional_light
{
	vec4 ambient_intensity;     // Ambient intensity for scene
	vec4 colour;                // Light colour
	vec3 direction;             // Direction of the light
} light;

	
uniform vec3 eye_position;		// Camera Position			
uniform sampler2D tex;

in vec3 vertex_position;
in vec3 transformed_normal;
in vec2 vertex_tex_coord;		// Incoming texture coordinate

// Outgoing colour
out vec4 col;

void main() {

  /*
   * Calculate ambient light
   */
  vec4 ambient = mat.diffuse_reflection * light.ambient_intensity;

  /*
   * Calculate diffuse light
   */
  float k = max(dot(transformed_normal, light.direction), 0.0);
  // Calculate dot product
  vec4 diffuse = k * (mat.diffuse_reflection * light.colour);

  // Calculate view direction
  vec3 view_direction = normalize(eye_position - vertex_position);

  // Calculate half_vector
  vec3 half_vector = normalize(light.direction + view_direction);

  /*
   * Calculate specular lighting
   *
   * Calculate specular intensity
   */
  float s = pow(max(dot(transformed_normal, half_vector), 0.0), mat.shininess);
  vec4 specular = (mat.specular_reflection * light.colour) * s;

   /*
    * Output primary colour
    */
   vec4 primary_colour = mat.emissive + ambient + diffuse;

   /*
    * Output secondary colour
    */
    vec4 secondary_colour = specular;

    // Sample texutre
    vec4 tex_colour = texture(tex, vertex_tex_coord);

    // Calculate final fragment colour
    col = (primary_colour  * tex_colour) + secondary_colour;
	col.a = 1.0;
}
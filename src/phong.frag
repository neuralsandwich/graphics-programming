#version 400

uniform vec4 emissive;				// Emissive light values
uniform vec4 material_colour;		// the material of the object
uniform vec4 ambient_intensity;     // Ambient intensity for scene
uniform vec4 light_colour;			// Light colour
uniform vec4 specular_colour;		// Colour for specular material
uniform vec3 light_direction;		// Direction of the light
uniform vec3 eye_position;			// Camera Position
uniform float shininess;			// Materials shininess factor
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
  vec4 ambient = ambient_intensity * material_colour;

  /*
   * Calculate diffuse light
   */
  float k = max(dot(transformed_normal, light_direction), 0.0);
  // Calculate dot product
  vec4 diffuse = k * (material_colour * light_colour);

  // Calculate view direction
  vec3 view_direction = normalize(eye_position - vertex_position);

  // Calculate half_vector
  vec3 half_vector = normalize(light_direction + view_direction);

  /*
   * Calculate specular lighting
   *
   * Calculate specular intensity
   */
  float s = pow(max(dot(transformed_normal, half_vector), 0.0), shininess);
  vec4 specular = (specular_colour * light_colour) * s;

   /*
    * Output primary colour
    */
   vec4 primary_colour = emissive + ambient + diffuse;
   primary_colour.a = 1.0;

   /*
    * Output secondary colour
	*/
	vec4 secondary_colour = specular;
	secondary_colour.a = 1.0;

	// Sample texutre
	vec4 tex_colour = texture(tex, vertex_tex_coord);

	// Calculate final fragment colour
	col = (primary_colour  * tex_colour) + secondary_colour;
}
#version 400

layout (std140) uniform;

uniform material
{
    vec4 emissive;				 // Emissive light values
    vec4 diffuse_reflection;	 // Colour for diffuse light reflected from material 
    vec4 specular_reflection;    // Colour for specular light reflected from material 
    float shininess;             // Materials shininess factor
} mat;

uniform directional_light
{
    vec4 ambient_intensity;     // Ambient intensity for scene
    vec4 colour;                // Light colour
    vec3 direction;             // Direction of the light
} light;

uniform vec3 eye_position;		// Camera Position			
uniform sampler2D tex;          // Texuter Data
uniform sampler2D normal_map;   // Normal Map
uniform sampler2D specular_map; // Specular map

in vec3 transformed_position;
in vec3 light_dir;
in vec3 view_dir;
in vec2 vertex_tex_coord;		// Incoming texture coordinate

// Outgoing colour
out vec4 colour;

void main() {

  //vec4 diffuse = texture2D(tex, vertex_tex_coord);
  //vec3 normap = texture2D(normal_map, vertex_tex_coord);
    
  

  // Sample normal from the normal map
  vec3 normal = normalize(((texture(normal_map, vertex_tex_coord).rgb * 2.0) - vec3(1.0, 1.0, 1.0)));
  //vec3 normal = normalize((texture2D(normal_map, vertex_tex_coord) * 2.0 - 1.0));

  //Calculate ambient light
  vec4 ambient = mat.diffuse_reflection * light.ambient_intensity;

  // Calculate diffuse light
  vec4 diffuse = (mat.diffuse_reflection * light.colour) * max(dot(light.direction, normal), 0.0);
  //vec4 diffuse = (mat.diffuse_reflection * light.colour) * max(dot(light.direction, normal), 0.0);


  // Calculate half_vector
  vec3 half_vector = normalize(light_dir + view_dir);

  //Calculate specular lighting
  vec4 specular = (mat.specular_reflection * light.colour) * pow(max(dot(normal, half_vector), 0.0), mat.shininess) * texture(specular_map, vertex_tex_coord).a;

  // Sample texutre
  vec4 tex_colour = texture(tex, vertex_tex_coord);

  // Calculate final fragment colour
  colour = ((mat.emissive + ambient + diffuse)  * tex_colour) + specular;
}
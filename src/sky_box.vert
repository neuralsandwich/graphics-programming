#version 400
			
uniform mat4 MVP;					// Model-View-Projection matrix

layout (location = 0) in vec3 position;		// The vertex position in model space

// Output variables
out vec3 tex_coord;

void main()
{

  // Pass through the position
  tex_coord = position;
  
  // Transform position
  gl_Position = MVP * vec4(position, 1.0);

  // Using Logarithmic Depth to stop Z fighting on Earth atmosphere
  //gl_Position.z = log(1e-6 * gl_Position.z + 1) / log(1e-6 * 150e6 + 1) * gl_Position.w;
}
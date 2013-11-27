#version 400

// Cubemap data
uniform samplerCube cubemap;

in vec3 tex_coord;
out vec4 colour;

void main()
{
 // Sample cubemap at coord
 colour = texture(cubemap, tex_coord);
}
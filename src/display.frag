#version 400
        
uniform sampler2D tex;
uniform float offset;

in vec2 vertex_tex_coord; // Incoming texture coordinate

// Outgoing colour
out vec4 col;

void main() {
    vec2 texcoord = vertex_tex_coord;
    // Calculate final fragment colour
    col = texture(tex, vertex_tex_coord);
}
#version 400
        
uniform sampler2D tex;

in vec2 vertex_tex_coord;		// Incoming texture coordinate

// Outgoing colour
out vec4 col;

void main() {
    // Calculate final fragment colour
    col = texture(tex, vertex_tex_coord);
}
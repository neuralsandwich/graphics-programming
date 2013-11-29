#version 400
        
uniform sampler2D tex;

in vec2 vertex_tex_coord;		// Incoming texture coordinate

// Outgoing colour
out vec4 col;

void main() {
    float dx = 10.*(1./512);
    float dy = 10.*(1./512.);
    vec2 coord = vec2(dx*floor(vertex_tex_coord.x/dx),
                      dy*floor(vertex_tex_coord.y/dy));
    col = texture2D(tex, coord);
}
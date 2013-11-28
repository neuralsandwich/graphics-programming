#version 400
        
uniform sampler2D tex;

// 1.0f/screenwidth
uniform float inverse_width;
// 1.0f/screenheight
uniform float inverse_height;

// Surround pixels to sample and their scale
const vec4 samples[4] = vec4[4]
(
    vec4(-1.0, 0.0, 0.0, 0.25),
    vec4( 1.0, 0.0, 0.0, 0.25),
    vec4( 0.0, 1.0, 0.0, 0.25),
    vec4(0.0, -1.0, 0.0, 0.25)
);

in vec2 vertex_tex_coord; // Incoming texture coordinate

// Outgoing colour
out vec4 col;

void main() {
    
    for (int i = 0; i < 4; ++i) {
        vec2 tex_coord = vertex_tex_coord + vec2(samples[i].x * inverse_width, samples[i].y * inverse_height);
        col += samples[i].w * texture(tex, tex_coord);
    }

    // Calculate final fragment colour
    col.a = 1.0;
}
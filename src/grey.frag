#version 400
        
uniform sampler2D tex;

const vec3 intensity = vec3(0.299, 0.587, 0.184);

in vec2 vertex_tex_coord;		// Incoming texture coordinate

// Outgoing colour
out vec4 col;

void main() {
    // Calculate final fragment colour
    col = texture(tex, vertex_tex_coord);
    float grey = dot(col.rgb, intensity);
    col = vec4(grey);
    col.a = 1.0;
}
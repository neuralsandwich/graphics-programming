#version 400

// 1D texture
uniform sampler1D tex;

// Incoming texture coordinate
in float tex_coord;

// Outgoing colour
out vec4 col;

void main() {
  // Get colour from 1D texture

  col = texture(tex, tex_coord);
}
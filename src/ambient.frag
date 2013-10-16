#version 400

// Incoming texture coordinate
in vec4 vertex_colour;

// Outgoing colour
out vec4 col;

void main() {
  // Get colour from 1D texture

  col = vertex_colour;
}
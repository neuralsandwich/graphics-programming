uniform sampler2D tex;
uniform float offset;

in vec2 vertex_tex_coord;
 
void main(void) {
  vec2 texcoord = vertex_tex_coord;
  texcoord.x += sin(texcoord.y * 4*2*3.14159 + offset) / 100;
  gl_FragColor = texture2D(tex, texcoord);
}
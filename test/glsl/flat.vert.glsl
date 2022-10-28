#version 450

layout (location = 0) in vec3 a_pos;

layout (location = 0) out vec3 v_pos;

void main() {
  v_pos = a_pos + 0.5;
  gl_Position = vec4(a_pos, 1.0);
}

#version 450

layout (location = 0) in vec3 a_pos;

layout (location = 0) out vec3 v_pos;

layout (binding = 0) uniform ProjectionMatrix {
  mat4 matrix;
} u_projection;

void main() {
  v_pos = a_pos + 0.5;
  gl_Position = u_projection.matrix * vec4(a_pos, 1.0);
}

#version 450

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex;

layout (location = 0) out vec2 v_tex;

layout (binding = 0) uniform ProjectionMatrix {
  mat4 matrix;
} u_projection;

layout (binding = 1) uniform ModelMatrix {
  mat4 matrix;
} u_model;

void main() {
  v_tex = a_tex;
  gl_Position = u_projection.matrix * u_model.matrix * vec4(a_pos, 1.0);
  gl_Position.y *= -1;
}

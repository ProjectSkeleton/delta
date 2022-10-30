#version 450

layout (location = 0) in vec2 v_tex;

layout (location = 0) out vec4 o_color;

layout(binding = 2) uniform sampler2D u_test_texture;
layout(binding = 3) uniform sampler2D u_pepper_texture;

void main() {
  o_color = texture(u_test_texture, v_tex) * texture(u_pepper_texture, v_tex);
}

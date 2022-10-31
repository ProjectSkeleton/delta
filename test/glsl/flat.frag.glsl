#version 450

layout (location = 0) in vec2 v_tex;

layout (location = 0) out vec4 o_color;

layout(binding = 2) uniform sampler2D u_diffuse_texture;

void main() {
  o_color = texture(u_diffuse_texture, v_tex);
}

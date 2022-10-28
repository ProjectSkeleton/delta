#include <delta/delta.hh>

int main() {
  auto instance = Delta::CreateInstance();

  Delta::WindowCreateInfo window_info;
  window_info.clear_color = { 0.2f, 0.4f, 0.6f, 1.0f };
  auto window = instance->CreateWindow(window_info);

  Delta::ShaderCreateInfo shader_info;
  shader_info.spv_paths.vert_path = "spv/flat.vert.spv";
  shader_info.spv_paths.frag_path = "spv/flat.frag.spv";
  shader_info.render_target = window;
  auto shader = instance->CreateShader(shader_info);

  auto render_pass = instance->CreateRenderPass(window);
  render_pass->RecordBindShaderCommand(shader);

  while (window->IsOpen()) {
    window->PollEvents();
    render_pass->Execute();
  }
}

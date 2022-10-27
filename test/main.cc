#include <delta/delta.hh>

int main() {
  auto instance = Delta::CreateInstance();

  Delta::WindowCreateInfo window_info;
  window_info.clear_color = { 0.2f, 0.4f, 0.6f, 1.0f };
  auto window = instance->CreateWindow(window_info);

  auto render_pass = instance->CreateRenderPass(window);

  while (window->IsOpen()) {
    window->PollEvents();
    render_pass->Execute();
  }
}

#include <delta/delta.hh>

int main() {
  auto instance = Delta::CreateInstance();

  auto window = instance->CreateWindow();
  while (window->IsOpen()) {
    window->PollEvents();
    // Begin render pass (window)
    // Render geometry
    // End render pass
  }
}

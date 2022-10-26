#include <delta/delta.hh>

int main() {
  auto instance = Delta::CreateInstance(Delta::Backend::kOpenGl);

  auto window = instance->CreateWindow();
  while (window->IsOpen()) {
    // Poll input
    // Begin render pass (window)
    // Render geometry
    // End render pass
  }
}

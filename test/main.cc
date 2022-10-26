#include <delta/delta.hh>

int main() {
  auto instance = std::make_unique<Delta::DirectX11Instance>();

  auto window = instance->CreateWindow();
  while (window->IsOpen()) {
    // Poll input
    // Begin render pass (window)
    // Render geometry
    // End render pass
  }
}

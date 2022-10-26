#include "directx11_instance.hh"

#include "delta/backend/windows/windows_window.hh"

namespace Delta {

std::unique_ptr<Window> DirectX11Instance::CreateWindow() {
  return std::move(std::make_unique<WindowsWindow>());
}

}

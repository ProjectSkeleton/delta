#include "directx11_instance.hh"

#include "delta/backend/windows/windows_window.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

DirectX11Instance::DirectX11Instance() {
  throw InstanceCreateException("DirectX11 not yet supported");
}

std::unique_ptr<Window> DirectX11Instance::CreateWindow(const WindowCreateInfo& window_info) {
  return std::move(std::make_unique<WindowsWindow>(window_info));
}

}

#include "directx11_instance.hh"

#include "delta/backend/windows/windows_window.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

DirectX11Instance::DirectX11Instance() {
  throw InstanceCreateException("DirectX11 not yet supported");
}

std::shared_ptr<Window> DirectX11Instance::CreateWindow(const WindowCreateInfo& window_info) {
  return std::make_shared<WindowsWindow>(window_info);
}

std::shared_ptr<RenderPass> DirectX11Instance::CreateRenderPass(const std::shared_ptr<RenderTarget>& render_target) {
  return nullptr;
}

std::shared_ptr<Shader> DirectX11Instance::CreateShader(const ShaderCreateInfo& shader_info) {
  return nullptr;
}

}

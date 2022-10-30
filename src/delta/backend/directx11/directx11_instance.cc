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

std::shared_ptr<Mesh> DirectX11Instance::CreateMesh(const MeshCreateInfo& mesh_info) {
  return nullptr;
}

std::shared_ptr<Texture> DirectX11Instance::CreateTexture(const std::string& path) {
  return nullptr;
}

std::shared_ptr<Texture> DirectX11Instance::CreateTexture(const TextureInfo& texture_info) {
  return nullptr;
}

std::shared_ptr<Texture> DirectX11Instance::CreateTexture(const BlankTextureInfo& blank_texture_info) {
  return nullptr;
}

}

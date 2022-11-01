#include "vulkan_instance.hh"

#include "delta/backend/vulkan/vulkan_window.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

VulkanInstance::VulkanInstance() {
  throw InstanceCreateException("Vulkan not yet supported");
}

std::shared_ptr<Window> VulkanInstance::CreateWindow(const WindowInfo& window_info) {
  return std::make_shared<VulkanWindow>(window_info);
}

std::shared_ptr<RenderPass> VulkanInstance::CreateRenderPass(const RenderPassInfo& render_pass_info) {
  return nullptr;
}

std::shared_ptr<Shader> VulkanInstance::CreateShader(const ShaderInfo& shader_info) {
  return nullptr;
}

std::shared_ptr<Mesh> VulkanInstance::CreateMesh(const MeshInfo& mesh_info) {
  return nullptr;
}

std::shared_ptr<FrameBuffer> VulkanInstance::CreateFrameBuffer(const FrameBufferInfo& frame_buffer_info) {
  return nullptr;
}

std::shared_ptr<Texture2d> VulkanInstance::CreateTexture2d(const std::string& path) {
  return nullptr;
}

std::shared_ptr<Texture2d> VulkanInstance::CreateTexture2d(const Texture2dInfo& texture_info) {
  return nullptr;
}

std::shared_ptr<Texture2d> VulkanInstance::CreateTexture2d(const BlankTexture2dInfo& blank_texture_info) {
  return nullptr;
}

std::shared_ptr<Texture2d> VulkanInstance::CreateTexture2d(const Color& color) {
  return nullptr;
}

}

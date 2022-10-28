#include "vulkan_instance.hh"

#include "delta/backend/vulkan/vulkan_window.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

VulkanInstance::VulkanInstance() {
  throw InstanceCreateException("Vulkan not yet supported");
}

std::shared_ptr<Window> VulkanInstance::CreateWindow(const WindowCreateInfo& window_info) {
  return std::make_shared<VulkanWindow>(window_info);
}

std::shared_ptr<RenderPass> VulkanInstance::CreateRenderPass(const std::shared_ptr<RenderTarget>& render_target) {
  return nullptr;
}

std::shared_ptr<Shader> VulkanInstance::CreateShader(const ShaderCreateInfo& shader_info) {
  return nullptr;
}

}

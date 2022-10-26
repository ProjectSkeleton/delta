#include "vulkan_instance.hh"

#include "delta/backend/vulkan/vulkan_window.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

VulkanInstance::VulkanInstance() {
  throw InstanceCreateException("Vulkan not yet supported");
}

std::unique_ptr<Window> VulkanInstance::CreateWindow(const WindowCreateInfo& window_info) {
  return std::move(std::make_unique<VulkanWindow>(window_info));
}

}

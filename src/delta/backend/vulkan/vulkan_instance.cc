#include "vulkan_instance.hh"

#include "delta/backend/vulkan/vulkan_window.hh"

namespace Delta {

std::unique_ptr<Window> VulkanInstance::CreateWindow() {
  return std::move(std::make_unique<VulkanWindow>());
}

}

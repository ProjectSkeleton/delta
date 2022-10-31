#include "instance.hh"

#include <vector>

#include "delta/backend/opengl/opengl_instance.hh"
#if defined(DELTA_HAS_VULKAN)
  #include "delta/backend/vulkan/vulkan_instance.hh"
#endif
#if defined(_WIN32)
  #include "delta/backend/directx11/directx11_instance.hh"
#elif defined(__APPLE__)
  #include "delta/backend/metal/metal_instance.hh"
#endif
#include "delta/delta/utils/exceptions.hh"
#include "delta/delta/utils/logger.hh"

namespace Delta {

std::shared_ptr<Instance> CreateInstance(Backend preferred_backend) {
#if defined(_WIN32)
  if (preferred_backend == Backend::kNone) { preferred_backend = Backend::kDirectX11; }
#elif defined(__APPLE__)
  if (preferred_backend == Backend::kNone) { preferred_backend = Backend::kMetal; }
#elif defined(__linux__)
  if (preferred_backend == Backend::kNone) { preferred_backend = Backend::kVulkan; }
#endif

  std::vector<Backend> possible_backends = {
#if defined(__APPLE__)
    Backend::kMetal,
#elif defined(_WIN32)
    Backend::kDirectX11,
#endif
#if defined(DELTA_HAS_VULKAN)
    Backend::kVulkan,
#endif
    Backend::kOpenGl };

  Logger temp_logger;
  Backend current_backend = preferred_backend;

  while (!possible_backends.empty()) {
    try {
      switch (current_backend) {
        case Backend::kOpenGl: return std::make_shared<OpenGlInstance>();
#if defined(DELTA_HAS_VULKAN)
        case Backend::kVulkan: return std::make_shared<VulkanInstance>();
#endif
#if defined(_WIN32)
        case Backend::kDirectX11: return std::make_shared<DirectX11Instance>();
#elif defined(__APPLE__)
        case Backend::kMetal: return std::make_shared<MetalInstance>();
#endif
        default: return nullptr;
      }
    }
    catch (const InstanceCreateException& e) {
      temp_logger.Log(LogSeverity::kError, e.what());
      possible_backends.erase(std::remove(possible_backends.begin(), possible_backends.end(), current_backend), possible_backends.end());
      if (!possible_backends.empty()) {
        current_backend = possible_backends[0];
      }
    }
  }

  temp_logger.Log(LogSeverity::kFatal, "Unable to create instance");
  return nullptr;
}

}

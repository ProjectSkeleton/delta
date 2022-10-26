#include "instance.hh"

#include <vector>

#include "delta/backend/opengl/opengl_instance.hh"
#include "delta/backend/vulkan/vulkan_instance.hh"
#if defined(_WIN32)
  #include "delta/backend/directx11/directx11_instance.hh"
#elif defined(__APPLE__)
  #include "delta/backend/metal/metal_instance.hh"
#endif
#include "delta/delta/utils/exceptions.hh"
#include "delta/delta/utils/logger.hh"

namespace Delta {

std::unique_ptr<Instance> CreateInstance(Backend preferred_backend) {
#if defined(_WIN32)
  if (preferred_backend == Backend::kNone) { preferred_backend = Backend::kDirectX11; }
  std::vector<Backend> possible_backends = { Backend::kDirectX11, Backend::kVulkan, Backend::kOpenGl };
#elif defined(__APPLE__)
  if (preferred_backend == Backend::kNone) { preferred_backend = Backend::kMetal; }
  std::vector<Backend> possible_backends = { Backend::Metal, Backend::kVulkan, Backend::kOpenGl };
#elif defined(__linux__)
  if (preferred_backend == Backend::kNone) { preferred_backend = Backend::kVulkan; }
  std::vector<Backend> possible_backends = { Backend::kVulkan, Backend::kOpenGl };
#endif

  Logger temp_logger;
  Backend current_backend = preferred_backend;

  while (!possible_backends.empty()) {
    try {
      switch (current_backend) {
        case Backend::kOpenGl: return std::make_unique<OpenGlInstance>();
        case Backend::kVulkan: return std::make_unique<VulkanInstance>();
#if defined(_WIN32)
        case Backend::kDirectX11: return std::make_unique<DirectX11Instance>();
#elif defined(__APPLE__)
        case Backend::kMetal: return std::make_unique<MetalInstance>();
#endif
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

  return nullptr;
}

}

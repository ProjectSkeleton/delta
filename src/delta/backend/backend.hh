#pragma once

namespace Delta {

enum class Backend {
  kNone,
  kOpenGl,
#if defined(DELTA_HAS_VULKAN)
  kVulkan,
#endif
#if defined(_WIN32)
  kDirectX11,
#elif defined(__APPLE__)
  kMetal
#endif
};

}

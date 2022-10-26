#pragma once

namespace Delta {

enum class Backend {
  kNone,
  kOpenGl,
  kVulkan,
#if defined(_WIN32)
  kDirectX11,
#elif defined(__APPLE__)
  kMetal
#endif
};

}

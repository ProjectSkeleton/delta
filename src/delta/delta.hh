#pragma once

#include "delta/backend/opengl/opengl_instance.hh"
#if defined(DELTA_HAS_VULKAN)
  #include "delta/backend/vulkan/vulkan_instance.hh"
#endif
#if defined(_WIN32)
  #include "delta/backend/directx11/directx11_instance.hh"
#endif

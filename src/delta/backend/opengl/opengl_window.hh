#pragma once

#include "delta/backend/glfw/glfw_window.hh"

namespace Delta {

class OpenGlWindow : public GlfwWindow {
public:
  OpenGlWindow(const WindowCreateInfo& window_info);
};

}

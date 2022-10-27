#include "opengl_window.hh"

#include <GLFW/glfw3.h>

namespace Delta {

OpenGlWindow::OpenGlWindow(const WindowCreateInfo& window_info) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#if defined(__APPLE__)
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

#if defined(NDEBUG)
  const char* title = window_info.title.empty() ? "Delta | OpenGl" : window_info.title.c_str();
#else
  const char* title = window_info.title.empty() ? "Delta | OpenGl | Debug" : window_info.title.c_str();
#endif
  glfw_window_ = glfwCreateWindow((int)window_info.width, (int)window_info.height, title, nullptr, nullptr);

  glfwSwapInterval(window_info.enable_vsync ? 1 : 0);

  Center();
}

}

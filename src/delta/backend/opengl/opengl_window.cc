#include "opengl_window.hh"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Delta {

OpenGlWindow::OpenGlWindow(const WindowCreateInfo& window_info) : enable_depth_test_(window_info.enable_depth_test), clear_color_(window_info.clear_color) {
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

  // TODO: This might have to move to BindRenderTarget
  glfwMakeContextCurrent(glfw_window_);
  int version = gladLoadGL(glfwGetProcAddress);
  glViewport(0, 0, (GLsizei)window_info.width, (GLsizei)window_info.height);

  glfwSwapInterval(window_info.enable_vsync ? 1 : 0);

  Center();
}

void OpenGlWindow::OnRenderPassBegin() {
  // TODO: Bind window framebuffer
  enable_depth_test_ ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
  glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a);
  glClear(GL_COLOR_BUFFER_BIT | (enable_depth_test_ ? GL_DEPTH_BUFFER_BIT : 0));
}

void OpenGlWindow::OnRenderPassComplete() {
  glfwSwapBuffers(glfw_window_);
}

}

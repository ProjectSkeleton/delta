#include "opengl_window.hh"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Delta {

const static int kSuitableOpenGLVersions[8][2] = { {4,6}, {4,5}, {4,4}, {4,3}, {4,2}, {4,1}, {4,0}, {3,3} };

OpenGlWindow::OpenGlWindow(const WindowInfo& window_info) {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

  // Find highest supported gl version
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  for (size_t i = 0; i < sizeof(kSuitableOpenGLVersions) / sizeof(kSuitableOpenGLVersions[0]); ++i) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, kSuitableOpenGLVersions[i][0]);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, kSuitableOpenGLVersions[i][1]);
    GLFWwindow* offscreen_context = glfwCreateWindow(1, 1, "", nullptr, nullptr);
    if (offscreen_context) {
      glfwDestroyWindow(offscreen_context);
      break;
    }
  }
  glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

#if defined(__APPLE__)
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#if defined(NDEBUG)
  const char* title = window_info.title.empty() ? "Delta | OpenGl" : window_info.title.c_str();
#else
  const char* title = window_info.title.empty() ? "Delta | OpenGl | Debug" : window_info.title.c_str();
#endif
  glfw_window_ = glfwCreateWindow((int)window_info.width, (int)window_info.height, title, nullptr, nullptr);

  Center();

  // TODO: This might have to move to BindRenderTarget
  glfwMakeContextCurrent(glfw_window_);
  (void)gladLoadGL(glfwGetProcAddress);

  glfwGetFramebufferSize(glfw_window_, &width_, &height_);

  glfwSwapInterval(window_info.enable_vsync ? 1 : 0);

  glfwSetWindowUserPointer(glfw_window_, this);
  glfwSetFramebufferSizeCallback(glfw_window_, [](GLFWwindow* glfw_window, int width, int height) {
    OpenGlWindow* win = (OpenGlWindow*)glfwGetWindowUserPointer(glfw_window);
    win->width_ = width;
    win->height_ = height;
    glViewport(0, 0, width, height);
    if (win->resize_callback_) {
      win->resize_callback_(width, height);
    }
  });
}

void OpenGlWindow::OnRenderPassBegin(const RenderPassInfo& render_pass_info) {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, width_, height_);

  if (render_pass_info.on_begin == RenderPassBeginOp::kClear) {
    glClearColor(render_pass_info.clear_color.r, render_pass_info.clear_color.g, render_pass_info.clear_color.b, render_pass_info.clear_color.a);
    if (render_pass_info.enable_depth_test) {
      glEnable(GL_DEPTH_TEST);
    }
    else {
      glDisable(GL_DEPTH_TEST);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
}

void OpenGlWindow::OnRenderPassComplete(const RenderPassInfo& render_pass_info) {
  if (render_pass_info.on_complete == RenderPassCompleteOp::kSwapchainPresent) {
    glfwSwapBuffers(glfw_window_);
  }
}

void OpenGlWindow::SetResizeCallback(WindowResizeCallback callback) {
  resize_callback_ = callback;
  int w, h;
  glfwGetFramebufferSize(glfw_window_, &w, &h);
  resize_callback_(w, h);
}

}

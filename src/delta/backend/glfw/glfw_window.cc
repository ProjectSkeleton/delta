#include "glfw_window.hh"

#include <GLFW/glfw3.h>

namespace Delta {

static int num_glfw_windows_ = 0;

GlfwWindow::GlfwWindow() {
  if (num_glfw_windows_ == 0) {
    glfwInit();
  }
  ++num_glfw_windows_;
}

GlfwWindow::~GlfwWindow() {
  glfwDestroyWindow(glfw_window_);

  --num_glfw_windows_;
  if (num_glfw_windows_ == 0) {
    glfwTerminate();
  }
}

bool GlfwWindow::IsOpen() const {
  return !glfwWindowShouldClose(glfw_window_);
}

void GlfwWindow::PollEvents() {
  glfwPollEvents();
}

GLFWmonitor* FindBestMonitor(GLFWwindow* glfw_window) {
  int monitor_count;
  GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);

  int window_x, window_y, window_width, window_height;
  glfwGetWindowSize(glfw_window, &window_width, &window_height);
  glfwGetWindowPos(glfw_window, &window_x, &window_y);

  GLFWmonitor* best_monitor = nullptr;
  int best_area = 0;

  for (int i = 0; i < monitor_count; ++i)
  {
    GLFWmonitor* monitor = monitors[i];

    int monitor_x, monitor_y;
    glfwGetMonitorPos(monitor, &monitor_x, &monitor_y);

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) continue;

    int area_min_x = std::max(window_x, monitor_x);
    int area_min_y = std::max(window_x, monitor_y);

    int area_max_x = std::min(window_x + window_width, monitor_x + mode->width);
    int area_max_y = std::min(window_x + window_height, monitor_x + mode->height);

    int area = (area_max_x - area_min_x) * (area_max_y - area_min_y);

    if (area > best_area) {
      best_area = area;
      best_monitor = monitor;
    }
  }

  return best_monitor;
}

void GlfwWindow::Center(bool center_horizontal, bool center_vertical) {
  GLFWmonitor* current_monitor = FindBestMonitor(glfw_window_);
  const GLFWvidmode* mode = glfwGetVideoMode(current_monitor);
  if (!mode) return;

  int monitor_x, monitor_y;
  glfwGetMonitorPos(current_monitor, &monitor_x, &monitor_y);

  int window_width, window_height;
  glfwGetWindowSize(glfw_window_, &window_width, &window_height);

  int old_window_x;
  int old_window_y;
  glfwGetWindowPos(glfw_window_, &old_window_x, &old_window_y);

  int window_x = center_horizontal ? (monitor_x + (mode->width - window_width) / 2) : old_window_x;
  int window_y = center_vertical ? (monitor_y + (mode->height - window_height) / 2) : old_window_y;
  glfwSetWindowPos(glfw_window_, window_x, window_y);
}

}

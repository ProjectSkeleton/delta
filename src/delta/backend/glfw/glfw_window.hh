#pragma once

#include "delta/delta/window.hh"

struct GLFWwindow;

namespace Delta {

class GlfwWindow : public Window {
public:
  GlfwWindow();
  ~GlfwWindow();

public:
  virtual bool IsOpen() const override;
  virtual void PollEvents() override;

protected:
  void Center(bool center_horizontal = true, bool center_vertical = true);

protected:
  GLFWwindow* glfw_window_ = nullptr;
};

}

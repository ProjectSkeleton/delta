#pragma once

#include "delta/backend/glfw/glfw_window.hh"
#include "delta/backend/opengl/opengl_instance.hh"

namespace Delta {

class OpenGlWindow : public GlfwWindow {
public:
  OpenGlWindow(const WindowCreateInfo& window_info);

public:
  virtual void OnRenderPassBegin() override;
  virtual void OnRenderPassComplete() override;

private:
  bool enable_depth_test_;
  Color clear_color_;
};

}

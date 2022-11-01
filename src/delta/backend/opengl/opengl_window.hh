#pragma once

#include "delta/backend/glfw/glfw_window.hh"
#include "delta/backend/opengl/opengl_instance.hh"

namespace Delta {

class OpenGlWindow : public GlfwWindow {
public:
  OpenGlWindow(const WindowInfo& window_info);

public:
  virtual void OnRenderPassBegin(const RenderPassInfo& render_pass_info) override;
  virtual void OnRenderPassComplete(const RenderPassInfo& render_pass_info) override;

  virtual void SetResizeCallback(RenderTargetResizeCallback callback) override;

private:
  RenderTargetResizeCallback resize_callback_;

  int width_, height_;
};

}

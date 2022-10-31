#pragma once

#include "delta/backend/glfw/glfw_window.hh"

namespace Delta {

class VulkanWindow : public GlfwWindow {
public:
  VulkanWindow(const WindowInfo& window_info);

public:
  virtual void OnRenderPassBegin(const RenderPassInfo& render_pass_info) override;
  virtual void OnRenderPassComplete(const RenderPassInfo& render_pass_info) override;

  virtual void SetResizeCallback(WindowResizeCallback callback) override;
};

}

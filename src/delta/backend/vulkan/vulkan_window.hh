#pragma once

#include "delta/backend/glfw/glfw_window.hh"

namespace Delta {

class VulkanWindow : public GlfwWindow {
public:
  VulkanWindow(const WindowCreateInfo& window_info);

public:
  virtual void OnRenderPassBegin() override;
  virtual void OnRenderPassComplete() override;

  virtual void SetResizeCallback(WindowResizeCallback callback) override;
};

}

#pragma once

#include "delta/delta/window.hh"

namespace Delta {

class WindowsWindow : public Window {
public:
  WindowsWindow(const WindowInfo& window_info);

public:
  virtual bool IsOpen() const override;
  virtual void PollEvents() override;

  virtual void OnRenderPassBegin(const RenderPassInfo& render_pass_info) override;
  virtual void OnRenderPassComplete(const RenderPassInfo& render_pass_info) override;

  virtual void SetResizeCallback(WindowResizeCallback callback) override;
};

}

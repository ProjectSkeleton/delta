#pragma once

#include "delta/delta/window.hh"

namespace Delta {

class WindowsWindow : public Window {
public:
  WindowsWindow(const WindowCreateInfo& window_info);

public:
  virtual bool IsOpen() const override;
  virtual void PollEvents() override;

  virtual void OnRenderPassBegin() override;
  virtual void OnRenderPassComplete() override;
};

}

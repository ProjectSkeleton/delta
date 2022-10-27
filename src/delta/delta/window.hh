#pragma once

#include <cstddef>
#include <string>

#include "delta/delta/render_target.hh"

namespace Delta {

struct WindowCreateInfo {
  size_t width = 1280;
  size_t height = 720;
  std::string title;
  bool enable_vsync = true;
};

class Window : public RenderTarget {
public:
  virtual bool IsOpen() const = 0;
  virtual void PollEvents() = 0;
};

}

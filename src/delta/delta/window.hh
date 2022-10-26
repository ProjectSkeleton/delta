#pragma once

#include "delta/delta/render_target.hh"

namespace Delta {

class Window : public RenderTarget {
public:
  virtual bool IsOpen() const = 0;
};

}

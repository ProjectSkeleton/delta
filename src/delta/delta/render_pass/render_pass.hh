#pragma once

#include <cstdint>
#include <memory>

#include "delta/delta/color.hh"
#include "delta/delta/render_target.hh"

namespace Delta {

class RenderPass {
public:
  virtual void Execute() const = 0;
};

}

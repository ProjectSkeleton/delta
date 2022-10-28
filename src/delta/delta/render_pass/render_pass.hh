#pragma once

#include <memory>

#include "delta/delta/shader/shader.hh"

namespace Delta {

class RenderPass {
public:
  virtual void Execute() = 0;

  virtual void RecordBindShaderCommand(const std::shared_ptr<Shader>& shader) = 0;
};

}

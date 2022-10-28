#pragma once

#include <memory>

#include "delta/delta/shader/shader.hh"
#include "delta/delta/model/mesh.hh"

namespace Delta {

class RenderPass {
public:
  virtual void Execute() = 0;

  virtual void RecordBindShaderCommand(const std::shared_ptr<Shader>& shader) = 0;
  virtual void RecordRenderMeshCommand(const std::shared_ptr<Mesh>& mesh) = 0;
};

}

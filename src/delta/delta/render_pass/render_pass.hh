#pragma once

#include <memory>

#include "delta/delta/shader/shader.hh"
#include "delta/delta/model/mesh.hh"

namespace Delta {

enum class RenderPassBeginOp {
  kPreserveExistingContents,
  kClear,
  kDontCare,
};

enum class RenderPassCompleteOp {
  kPreserveExistingContents,
  kSwapchainPresent,
  kDontCare,
};

class RenderTarget;

struct RenderPassInfo {
  RenderPassBeginOp on_begin = RenderPassBeginOp::kClear;
  RenderPassCompleteOp on_complete = RenderPassCompleteOp::kSwapchainPresent;
  Color clear_color;
  bool enable_depth_test = true;
  std::shared_ptr<RenderTarget> render_target;
};

class RenderPass {
public:
  virtual void Execute() = 0;

  virtual void RecordBindShaderCommand(const std::shared_ptr<Shader>& shader) = 0;
  virtual void RecordRenderMeshCommand(const std::shared_ptr<Mesh>& mesh) = 0;
};

}

#pragma once

#include <memory>

#include "delta/delta/color.hh"
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

// TODO
// A render pass should be required to keep a list of referenced objects and they should not
// go out of scope and be deleted so long as the render pass is using them
// It should be enforced that all RenderPass implementations must implement this
};

}

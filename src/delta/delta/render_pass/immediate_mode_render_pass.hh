#pragma once

#include "delta/delta/render_pass/immediate_mode_render_pass_command_buffer.hh"
#include "delta/delta/render_pass/render_pass.hh"

namespace Delta {

class ImmediateModeRenderPass : public RenderPass {
public:
  ImmediateModeRenderPass(const std::shared_ptr<RenderTarget>& render_target);

public:
  virtual void Execute() const override;

protected:
  ImmediateModeRenderPassCommandBuffer command_buffer_;
  std::shared_ptr<RenderTarget> render_target_;
};

}

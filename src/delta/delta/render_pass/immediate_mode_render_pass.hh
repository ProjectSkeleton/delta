#pragma once

#include "delta/delta/render_pass/immediate_mode_render_pass_command_buffer.hh"
#include "delta/delta/render_pass/render_pass.hh"
#include "delta/delta/render_target.hh"

namespace Delta {

class ImmediateModeRenderPass : public RenderPass {
public:
  ImmediateModeRenderPass(const std::shared_ptr<RenderTarget>& render_target);

public:
  virtual void Execute() override;

  virtual void RecordBindShaderCommand(const std::shared_ptr<Shader>& shader) override;
  virtual void RecordRenderMeshCommand(const std::shared_ptr<Mesh>& mesh) override;

protected:
  virtual void ExecuteBindShaderCommand(Shader* shader) = 0;
  virtual void ExecuteRenderMeshCommand(Mesh* mesh) = 0;

protected:
  ImmediateModeRenderPassCommandBuffer command_buffer_;
  std::shared_ptr<RenderTarget> render_target_;
};

}

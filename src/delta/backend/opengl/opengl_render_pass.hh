#pragma once

#include "delta/delta/render_pass/immediate_mode_render_pass.hh"

namespace Delta {

class OpenGlRenderPass : public ImmediateModeRenderPass {
public:
  OpenGlRenderPass(const RenderPassInfo& render_target);

protected:
  virtual void ExecuteBindShaderCommand(Shader* shader) override;
  virtual void ExecuteRenderMeshCommand(Mesh* mesh) override;
};

}

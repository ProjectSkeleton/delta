#pragma once

#include "delta/delta/render_pass/immediate_mode_render_pass.hh"

namespace Delta {

class OpenGlRenderPass : public ImmediateModeRenderPass {
public:
  OpenGlRenderPass(const std::shared_ptr<RenderTarget>& render_target);
};

}

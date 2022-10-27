#include "opengl_render_pass.hh"

#include <glad/gl.h>

namespace Delta {

OpenGlRenderPass::OpenGlRenderPass(const std::shared_ptr<RenderTarget>& render_target) : ImmediateModeRenderPass(render_target) { }

}

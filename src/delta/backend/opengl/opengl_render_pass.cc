#include "opengl_render_pass.hh"

#include "delta/backend/opengl/opengl_shader.hh"

namespace Delta {

OpenGlRenderPass::OpenGlRenderPass(const std::shared_ptr<RenderTarget>& render_target) : ImmediateModeRenderPass(render_target) { }

void OpenGlRenderPass::ExecuteBindShaderCommand(Shader* shader) {
  OpenGlShader* ogl_shader = (OpenGlShader*)(shader);
  ogl_shader->Bind();
}

}

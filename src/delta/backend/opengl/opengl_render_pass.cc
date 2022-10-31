#include "opengl_render_pass.hh"

#include "delta/backend/opengl/opengl_shader.hh"
#include "delta/backend/opengl/opengl_mesh.hh"

namespace Delta {

OpenGlRenderPass::OpenGlRenderPass(const RenderPassInfo& render_pass_info) : ImmediateModeRenderPass(render_pass_info) { }

void OpenGlRenderPass::ExecuteBindShaderCommand(Shader* shader) {
  OpenGlShader* ogl_shader = (OpenGlShader*)(shader);
  ogl_shader->Bind();
}

void OpenGlRenderPass::ExecuteRenderMeshCommand(Mesh* mesh) {
  OpenGlMesh* ogl_mesh = (OpenGlMesh*)(mesh);
  ogl_mesh->Render();
}

}

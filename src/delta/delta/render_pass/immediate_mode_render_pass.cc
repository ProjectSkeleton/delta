#include "immediate_mode_render_pass.hh"

#include "delta/delta/render_pass/render_pass_opcode.hh"

namespace Delta {

ImmediateModeRenderPass::ImmediateModeRenderPass(const RenderPassInfo& render_pass_info) : render_pass_info_(render_pass_info) { }

void ImmediateModeRenderPass::Execute() {
  render_pass_info_.render_target->OnRenderPassBegin(render_pass_info_);

  size_t instruction_ptr = 0;
  while (instruction_ptr < command_buffer_.Size()) {
    RenderPassOpcode opcode = command_buffer_.Extract<RenderPassOpcode>(instruction_ptr);

    switch (opcode) {
      case RenderPassOpcode::kBindShader: {
        Shader* shader = command_buffer_.Extract<Shader*>(instruction_ptr);
        ExecuteBindShaderCommand(shader);
        break;
      }

      case RenderPassOpcode::kRenderMesh: {
        Mesh* mesh = command_buffer_.Extract<Mesh*>(instruction_ptr);
        ExecuteRenderMeshCommand(mesh);
        break;
      }

      default: break;
    }
  }

  render_pass_info_.render_target->OnRenderPassComplete(render_pass_info_);
}

void ImmediateModeRenderPass::RecordBindShaderCommand(const std::shared_ptr<Shader>& shader) {
  command_buffer_.Push(RenderPassOpcode::kBindShader);
  command_buffer_.Push(shader.get());
  referenced_shaders_.push_back(shader);
}

void ImmediateModeRenderPass::RecordRenderMeshCommand(const std::shared_ptr<Mesh>& mesh) {
  command_buffer_.Push(RenderPassOpcode::kRenderMesh);
  command_buffer_.Push(mesh.get());
  referenced_meshes_.push_back(mesh);
}

}

#include "immediate_mode_render_pass.hh"

#include "delta/delta/render_pass/render_pass_opcode.hh"

namespace Delta {

ImmediateModeRenderPass::ImmediateModeRenderPass(const std::shared_ptr<RenderTarget>& render_target) : render_target_(render_target) { }

void ImmediateModeRenderPass::Execute() {
  render_target_->OnRenderPassBegin();

  size_t instruction_ptr = 0;
  while (instruction_ptr < command_buffer_.Size()) {
    RenderPassOpcode opcode = command_buffer_.Extract<RenderPassOpcode>(instruction_ptr);

    switch (opcode) {
      case RenderPassOpcode::kBindShader: {
        Shader* shader = command_buffer_.Extract<Shader*>(instruction_ptr);
        ExecuteBindShaderCommand(shader);
        break;
      }

      default: break;
    }
  }

  render_target_->OnRenderPassComplete();
}

void ImmediateModeRenderPass::RecordBindShaderCommand(const std::shared_ptr<Shader>& shader) {
  command_buffer_.Push(RenderPassOpcode::kBindShader);
  command_buffer_.Push(shader.get());
}

}

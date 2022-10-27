#include "immediate_mode_render_pass.hh"

#include "delta/delta/render_pass/render_pass_opcode.hh"

namespace Delta {

ImmediateModeRenderPass::ImmediateModeRenderPass(const std::shared_ptr<RenderTarget>& render_target) : render_target_(render_target) { }

void ImmediateModeRenderPass::Execute() const {
  render_target_->OnRenderPassBegin();

  size_t instruction_ptr = 0;
  while (instruction_ptr < command_buffer_.Size()) {
    RenderPassOpcode opcode = command_buffer_.Extract<RenderPassOpcode>(instruction_ptr);

    switch (opcode) {
      /*
      case RenderPassOpcode::kClear: {
        Color clear_color = command_buffer_.Extract<Color>(instruction_ptr);
        ExecuteClearCommand(clear_color);
        break;
      }
      */

      default: break;
    }
  }

  render_target_->OnRenderPassComplete();
}

}

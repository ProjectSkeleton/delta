#include "opengl_sampler_2d.hh"

#include <glad/gl.h>

#include "delta/backend/opengl/opengl_frame_buffer.hh"
#include "delta/backend/opengl/opengl_texture_2d.hh"

namespace Delta {

OpenGlSampler2d::OpenGlSampler2d(const Sampler2dInfo& sampler_info, unsigned int shader_program, unsigned int texture_slot) 
    : Sampler2d(sampler_info), shader_program_(shader_program), texture_slot_(texture_slot) {
  // Shader is already bound at this point
  glUniform1i(glGetUniformLocation(shader_program, sampler_info.name.c_str()), texture_slot);
}

void OpenGlSampler2d::SetTexture(std::shared_ptr<Sampler2dBindTarget> target) {
  bound_target_ = target;
  BindTarget();
}

void OpenGlSampler2d::BindTarget() {
  glUseProgram(shader_program_);
  glActiveTexture(GL_TEXTURE0 + texture_slot_);

  if (bound_target_->IsFrameBuffer()) {
    OpenGlFrameBuffer* gl_frame_buffer = (OpenGlFrameBuffer*)bound_target_.get();
    gl_frame_buffer->BindColorAttachment();
  }
  else {
    OpenGlTexture2d* gl_texture = (OpenGlTexture2d*)bound_target_.get();
    gl_texture->Bind();
  }
}

}

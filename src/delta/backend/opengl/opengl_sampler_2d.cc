#include "opengl_sampler_2d.hh"

#include <glad/gl.h>

#include "delta/backend/opengl/opengl_frame_buffer.hh"
#include "delta/backend/opengl/opengl_texture.hh"

namespace Delta {

OpenGlSampler2d::OpenGlSampler2d(const Sampler2dInfo& sampler_info, unsigned int shader_program, unsigned int texture_slot) 
    : Sampler2d(sampler_info), shader_program_(shader_program), texture_slot_(texture_slot) {
  // Shader is already bound at this point
  glUniform1i(glGetUniformLocation(shader_program, sampler_info.name.c_str()), texture_slot);
}

void OpenGlSampler2d::SetTexture(std::shared_ptr<Texture> texture) {
  glUseProgram(shader_program_);
  glActiveTexture(GL_TEXTURE0 + texture_slot_);

  if (texture->IsFrameBuffer()) {
    OpenGlFrameBuffer* gl_texture = (OpenGlFrameBuffer*)texture.get();
    gl_texture->BindAsTexture();
  }
  else {
    OpenGlTexture* gl_texture = (OpenGlTexture*)texture.get();
    gl_texture->Bind();
  }
  bound_texture_ = texture;
}

}
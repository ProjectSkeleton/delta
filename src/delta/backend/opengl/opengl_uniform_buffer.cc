#include "opengl_uniform_buffer.hh"

#include <glad/gl.h>

namespace Delta {

OpenGlUniformBuffer::OpenGlUniformBuffer(unsigned int program_id, const UniformBufferInfo& uniform_info) : UniformBuffer(uniform_info) {
  // Index of block where uniform will be uploaded
  GLuint location = glGetUniformBlockIndex(program_id, uniform_info.uniform_block_name.c_str());
  // If location_ == -1, the uniform buffer was probably unused and got optimised away

  // Link the shader's uniform block to this uniform binding point
  glUniformBlockBinding(program_id, location, uniform_info.binding);
  
  // Create uniform buffer and assign memory for it
  glGenBuffers(1, &uniform_buffer_);
  glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer_);
  glBufferData(GL_UNIFORM_BUFFER, uniform_info.size, nullptr, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferRange(GL_UNIFORM_BUFFER, uniform_info.binding, uniform_buffer_, 0, uniform_info.size);
}

OpenGlUniformBuffer::~OpenGlUniformBuffer() {
  glDeleteBuffers(1, &uniform_buffer_);
}

void OpenGlUniformBuffer::Upload(const void* data) {
  glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer_);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, info_.size, data);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGlUniformBuffer::Upload(const std::string& member_name, const void* data) {
  const BufferElement& element = info_.layout[info_.member_indices.at(member_name)];
  glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer_);
  glBufferSubData(GL_UNIFORM_BUFFER, element.offset, element.size, data);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGlUniformBuffer::Upload(size_t member_index, const void* data) {
  const BufferElement& element = info_.layout[member_index];
  glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer_);
  glBufferSubData(GL_UNIFORM_BUFFER, element.offset, element.size, data);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

}

#pragma once

#include <cstddef>

#include "delta/delta/shader/uniform_buffer.hh"

namespace Delta {

class OpenGlUniformBuffer : public UniformBuffer {
public:
  OpenGlUniformBuffer(unsigned int program_id, const UniformBufferInfo& uniform_info);
  ~OpenGlUniformBuffer();

public:
  virtual void Upload(const void* data) override;
  virtual void Upload(const std::string& member_name, const void* data) override;
  virtual void Upload(size_t member_index, const void* data) override;

private:
  unsigned int uniform_buffer_;
};

}

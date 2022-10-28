#pragma once

#include <cstdint>
#include <cstddef>
#include <string>

#include "delta/delta/model/buffer_layout.hh"
#include "delta/delta/shader/shader_stage.hh"

namespace Delta {

struct UniformBufferInfo {
  uint32_t binding;
  ShaderStage stage;
  size_t size;
  std::string name;
  std::string uniform_block_name;

  BufferLayout layout;
};

class UniformBuffer {
public:
  UniformBuffer(const UniformBufferInfo& uniform_info);

private:
  UniformBufferInfo info_;
};

}

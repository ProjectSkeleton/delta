#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "delta/delta/model/buffer_layout.hh"
#include "delta/delta/shader/shader_stage.hh"

namespace Delta {

struct UniformBufferInfo {
  uint32_t binding;
  ShaderStage stage;
  size_t size;
  std::string name;
  std::string uniform_block_name;

  std::unordered_map<std::string, size_t> member_indices;
  BufferLayout layout;
};

class UniformBuffer {
public:
  UniformBuffer(const UniformBufferInfo& uniform_info);

public:
  inline const std::string& GetName() { return info_.name; }

public:
  virtual void Upload(const void* data) = 0;
  virtual void Upload(float f);
  virtual void Upload(const glm::vec2& vec);
  virtual void Upload(const glm::vec3& vec);
  virtual void Upload(const glm::vec4& vec);
  virtual void Upload(const glm::mat4& matrix);

  virtual void Upload(const std::string& member_name, const void* data) = 0;
  virtual void Upload(const std::string& member_name, float f);
  virtual void Upload(const std::string& member_name, const glm::vec2& vec);
  virtual void Upload(const std::string& member_name, const glm::vec3& vec);
  virtual void Upload(const std::string& member_name, const glm::vec4& vec);
  virtual void Upload(const std::string& member_name, const glm::mat4& matrix);

  virtual void Upload(size_t member_index, const void* data) = 0;
  virtual void Upload(size_t member_index, float f);
  virtual void Upload(size_t member_index, const glm::vec2& vec);
  virtual void Upload(size_t member_index, const glm::vec3& vec);
  virtual void Upload(size_t member_index, const glm::vec4& vec);
  virtual void Upload(size_t member_index, const glm::mat4& matrix);

protected:
  UniformBufferInfo info_;
};

}

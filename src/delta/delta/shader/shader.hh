#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#include "delta/delta/model/buffer_layout.hh"
#include "delta/delta/shader/shader_stage.hh"
#include "delta/delta/render_target.hh"
#include "delta/delta/shader/uniform_buffer.hh"
#include "delta/delta/texture/sampler_2d.hh"

namespace Delta {

struct ShaderSourcePaths {
  std::string vert_path;
  std::string frag_path;
};

struct ShaderCreateInfo {
  ShaderSourcePaths spv_paths;
  std::shared_ptr<RenderTarget> render_target;
};

class Shader {
public:
  inline const BufferLayout& GetVertexInputLayout() { return vertex_input_layout_; };

  inline std::shared_ptr<UniformBuffer> GetUniformBuffer(uint32_t binding) { return uniform_buffers_[binding]; };
  std::shared_ptr<UniformBuffer> GetUniformBuffer(const std::string& name);

  inline std::shared_ptr<Sampler2d> GetSampler2d(uint32_t binding) { return sampler_2ds_[binding]; };
  std::shared_ptr<Sampler2d> GetSampler2d(const std::string& name);

protected:
  static std::unordered_map<ShaderStage, std::vector<uint32_t>> LoadSpv(const ShaderSourcePaths& shader_source);

protected:
  void PerformReflection(const std::unordered_map<ShaderStage, std::vector<uint32_t>>& code_map);

protected:
  virtual void CreateUniformBuffer(const UniformBufferInfo& uniform_info) = 0;
  virtual void CreateSampler2d(const Sampler2dInfo& sampler_info) = 0;

protected:
  BufferLayout vertex_input_layout_;
  std::unordered_map<uint32_t, std::shared_ptr<UniformBuffer>> uniform_buffers_;
  std::unordered_map<uint32_t, std::shared_ptr<Sampler2d>> sampler_2ds_;
};

}

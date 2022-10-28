#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#include "delta/delta/render_target.hh"
#include "delta/delta/shader/shader_stage.hh"
#include "delta/delta/model/buffer_layout.hh"

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

protected:
  static std::unordered_map<ShaderStage, std::vector<uint32_t>> LoadSpv(const ShaderSourcePaths& shader_source);

  void PerformReflection(const std::unordered_map<ShaderStage, std::vector<uint32_t>>& code_map);

protected:
  BufferLayout vertex_input_layout_;
};

}

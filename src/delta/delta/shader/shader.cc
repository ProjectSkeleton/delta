#include "shader.hh"

#include <fstream>

#include "delta/delta/shader/shader_stage.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

std::vector<uint32_t> LoadSpvModule(const std::string& path) {
  std::ifstream file(path, std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    throw ShaderCreateException("Failed to open .spv file");
  }
  size_t file_size = (size_t)file.tellg();
  std::vector<uint32_t> buffer(file_size / sizeof(uint32_t));
  file.seekg(0);
  file.read((char*)buffer.data(), file_size);
  file.close();
  return buffer;
}

std::unordered_map<ShaderStage, std::vector<uint32_t>> Shader::LoadSpv(const ShaderSourcePaths& shader_paths) {
  std::unordered_map<ShaderStage, std::vector<uint32_t>> result;
  
  if (!shader_paths.vert_path.empty()) { result.emplace(ShaderStage::kVertexShader,   LoadSpvModule(shader_paths.vert_path)); }
  if (!shader_paths.frag_path.empty()) { result.emplace(ShaderStage::kFragmentShader, LoadSpvModule(shader_paths.frag_path)); }

  return result;
}

}

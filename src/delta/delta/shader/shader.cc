#include "shader.hh"

#include <fstream>

// spirv-cross is also included with the Vulkan SDK. Make sure not to #include <spirv-cross/spirv_xxx> as this will
// cause mismatched header and cpp files and you will end up with linker errors
#include <spirv_glsl.hpp>

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

ShaderDataType FindShaderInputVectorType(uint32_t size) {
  switch (size) {
    case 1:  return ShaderDataType::kFloat;
    case 2:  return ShaderDataType::kFloat2;
    case 3:  return ShaderDataType::kFloat3;
    case 4:  return ShaderDataType::kFloat4;
    default: return ShaderDataType::kUnknown;
  }
}

// TODO: This function is not bulletproof and needs further testing
ShaderDataType FindUniformMemberType(const spirv_cross::SPIRType& type) {
  switch (type.basetype) {
    case spirv_cross::SPIRType::Float: {
      switch (type.vecsize) {
        case 1: return ShaderDataType::kFloat;
        case 2: return ShaderDataType::kFloat2;
        case 3: return type.columns == 1 ? ShaderDataType::kFloat3 : ShaderDataType::kMatrix3;
        case 4: return type.columns == 1 ? ShaderDataType::kFloat4 : ShaderDataType::kMatrix4;
      }
      break;
    }
    case spirv_cross::SPIRType::Int: {
      switch (type.vecsize) {
        case 1: return ShaderDataType::kInt;
        case 2: return ShaderDataType::kInt2;
        case 3: return ShaderDataType::kInt3;
        case 4: return ShaderDataType::kInt4;
      }
      break;
    }
  }

  return ShaderDataType::kUnknown;
}

void Shader::PerformReflection(const std::unordered_map<ShaderStage, std::vector<uint32_t>>& code_map) {
  std::unordered_map<size_t, ShaderDataType> vertex_input_map;

  for (const auto& shader : code_map) {
    const ShaderStage current_stage = shader.first;

    spirv_cross::CompilerGLSL* glsl = new spirv_cross::CompilerGLSL(shader.second);
	  spirv_cross::ShaderResources* resources = new spirv_cross::ShaderResources(glsl->get_shader_resources());

    // Find vertex input vectors
    if (current_stage == ShaderStage::kVertexShader) {
		  for (auto& stage_input : resources->stage_inputs) {
        uint32_t location = glsl->get_decoration(stage_input.id, spv::DecorationLocation);
        spirv_cross::SPIRType type = glsl->get_type(stage_input.type_id);
        ShaderDataType data_type = FindShaderInputVectorType(type.vecsize);
        vertex_input_map.emplace(location, data_type);
      }
    }

    // Find uniforms
    for (auto& uniform : resources->uniform_buffers) {
      UniformBufferInfo uniform_info;
      uniform_info.binding = glsl->get_decoration(uniform.id, spv::DecorationBinding);
      uniform_info.stage = current_stage;
      uniform_info.size = glsl->get_declared_struct_size(glsl->get_type(uniform.base_type_id));
      uniform_info.name = glsl->get_name(uniform.id);
      uniform_info.uniform_block_name = glsl->get_name(uniform.base_type_id);

      std::vector<BufferElement> buffer_elements;
      for (size_t i = 0; i < glsl->get_type(uniform.base_type_id).member_types.size(); ++i) {
        BufferElement element(FindUniformMemberType(glsl->get_type(glsl->get_type(uniform.base_type_id).member_types[i])));
        element.name = glsl->get_member_name(uniform.base_type_id, (uint32_t)i);
        buffer_elements.push_back(element);
      }
      uniform_info.layout = buffer_elements;

      uniform_buffers_.emplace(uniform_info.binding, uniform_info);
    }

    delete resources;
    delete glsl;

  }

  // Populate vertex input BufferLayout
  std::vector<BufferElement> buffer_elements;
  for (uint32_t i = 0; i < vertex_input_map.size(); ++i) {
    buffer_elements.push_back(vertex_input_map.at(i));
  }
  vertex_input_layout_ = buffer_elements;
}

}

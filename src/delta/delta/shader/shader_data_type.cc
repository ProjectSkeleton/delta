#include "shader_data_type.hh"

namespace Delta {

size_t ShaderDataTypeSize(ShaderDataType data_type) {
  switch (data_type) {
    case ShaderDataType::kBool:    return (size_t)(4);
    case ShaderDataType::kInt:     return (size_t)(4);
    case ShaderDataType::kInt2:    return (size_t)(4 * 2);
    case ShaderDataType::kInt3:    return (size_t)(4 * 3);
    case ShaderDataType::kInt4:    return (size_t)(4 * 4);
    case ShaderDataType::kFloat:   return (size_t)(4);
    case ShaderDataType::kFloat2:  return (size_t)(4 * 2);
    case ShaderDataType::kFloat3:  return (size_t)(4 * 3);
    case ShaderDataType::kFloat4:  return (size_t)(4 * 4);
    case ShaderDataType::kMatrix3: return (size_t)(4 * 3 * 3);
    case ShaderDataType::kMatrix4: return (size_t)(4 * 4 * 4);
    default:                       return (size_t)(0);
  }
}

size_t ShaderDataTypeComponentCount(ShaderDataType data_type) {
  switch (data_type) {
    case ShaderDataType::kBool:    return (size_t)(1);
    case ShaderDataType::kInt:     return (size_t)(1);
    case ShaderDataType::kInt2:    return (size_t)(2);
    case ShaderDataType::kInt3:    return (size_t)(3);
    case ShaderDataType::kInt4:    return (size_t)(4);
    case ShaderDataType::kFloat:   return (size_t)(1);
    case ShaderDataType::kFloat2:  return (size_t)(2);
    case ShaderDataType::kFloat3:  return (size_t)(3);
    case ShaderDataType::kFloat4:  return (size_t)(4);
    case ShaderDataType::kMatrix3: return (size_t)(3 * 3);
    case ShaderDataType::kMatrix4: return (size_t)(4 * 4);
    default:                       return (size_t)(0);
  }
}

}

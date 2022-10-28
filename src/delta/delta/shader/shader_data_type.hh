#pragma once

#include <cstddef>

namespace Delta {

enum class ShaderDataType {
  kBool,
  kInt,     kInt2,   kInt3,   kInt4,
  kFloat,   kFloat2, kFloat3, kFloat4,
  kMatrix3, kMatrix4,
  kUnknown,
};

size_t ShaderDataTypeSize(ShaderDataType data_type);
size_t ShaderDataTypeComponentCount(ShaderDataType data_type);

}

#pragma once

#include <cstddef>
#include <string>

#include "delta/delta/shader/shader_data_type.hh"

namespace Delta {

struct BufferElement {
  BufferElement(ShaderDataType data_type) : data_type(data_type), size(ShaderDataTypeSize(data_type)), offset(0) { }

  ShaderDataType data_type;
  size_t size;
  size_t offset;

  std::string name;

  operator ShaderDataType() { return data_type; }
};

}

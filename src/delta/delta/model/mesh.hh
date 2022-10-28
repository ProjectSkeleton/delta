#pragma once

#include <vector>

#include "delta/delta/model/buffer_layout.hh"

namespace Delta {

struct MeshCreateInfo {
  BufferLayout vertex_layout;
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
};

class Mesh {
};

}

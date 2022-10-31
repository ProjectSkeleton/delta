#pragma once

#include "delta/delta/model/mesh.hh"

namespace Delta {

class OpenGlMesh : public Mesh {
public:
  OpenGlMesh(const MeshInfo& mesh_info);
  ~OpenGlMesh();

public:
  void Render() const;

private:
  unsigned int vertex_array_;
  unsigned int vertex_buffer_;
  unsigned int index_buffer_;
  unsigned int num_indices_;
};

}

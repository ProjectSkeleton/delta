#include "opengl_mesh.hh"

#include <glad/gl.h>

namespace Delta {

GLenum DeltaShaderDataTypeToOpenGlType(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::kBool:    return GL_BOOL;
    case ShaderDataType::kInt:     return GL_INT;
    case ShaderDataType::kInt2:    return GL_INT;
    case ShaderDataType::kInt3:    return GL_INT;
    case ShaderDataType::kInt4:    return GL_INT;
    case ShaderDataType::kFloat:   return GL_FLOAT;
    case ShaderDataType::kFloat2:  return GL_FLOAT;
    case ShaderDataType::kFloat3:  return GL_FLOAT;
    case ShaderDataType::kFloat4:  return GL_FLOAT;
    case ShaderDataType::kMatrix3: return GL_FLOAT;
    case ShaderDataType::kMatrix4: return GL_FLOAT;
    default:                       return -1;
  }
}

OpenGlMesh::OpenGlMesh(const MeshCreateInfo& mesh_info) {
  glGenVertexArrays(1, &vertex_array_);
  glBindVertexArray(vertex_array_);

  glGenBuffers(1, &vertex_buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, mesh_info.vertices.size() * sizeof(float), mesh_info.vertices.data(), GL_STATIC_DRAW);

  for (int i = 0; i < mesh_info.vertex_layout.GetNumElements(); ++i) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, (GLsizei)ShaderDataTypeComponentCount(mesh_info.vertex_layout[i]), 
      (GLsizei)DeltaShaderDataTypeToOpenGlType(mesh_info.vertex_layout[i]),
      GL_FALSE, 
      (GLsizei)mesh_info.vertex_layout.GetStride(), 
      (const void*)(uint64_t)mesh_info.vertex_layout[i].offset);
  }

  glGenBuffers(1, &index_buffer_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_info.indices.size() * sizeof(uint32_t), mesh_info.indices.data(), GL_STATIC_DRAW);
  num_indices_ = (unsigned int)mesh_info.indices.size();

  glBindVertexArray(0);
}


OpenGlMesh::~OpenGlMesh() {
  glDeleteBuffers(1, &index_buffer_);
  glDeleteBuffers(1, &vertex_buffer_);
  glDeleteVertexArrays(1, &vertex_array_);
}

void OpenGlMesh::Render() const {
  glBindVertexArray(vertex_array_);
  glDrawElements(GL_TRIANGLES, num_indices_, GL_UNSIGNED_INT, 0);
}

}

#include "uniform_buffer.hh"

#include <glm/gtc/type_ptr.hpp>

namespace Delta {

UniformBuffer::UniformBuffer(const UniformBufferInfo& uniform_info) : info_(uniform_info) { }

void UniformBuffer::Upload(float f) { Upload(&f); }
void UniformBuffer::Upload(const glm::vec2& vec) { Upload(glm::value_ptr(vec)); }
void UniformBuffer::Upload(const glm::vec3& vec) { Upload(glm::value_ptr(vec)); }
void UniformBuffer::Upload(const glm::vec4& vec) { Upload(glm::value_ptr(vec)); }
void UniformBuffer::Upload(const glm::mat4& matrix) { Upload(glm::value_ptr(matrix)); }

void UniformBuffer::Upload(const std::string& member_name, float f) { Upload(member_name, &f); }
void UniformBuffer::Upload(const std::string& member_name, const glm::vec2& vec) { Upload(member_name, glm::value_ptr(vec)); }
void UniformBuffer::Upload(const std::string& member_name, const glm::vec3& vec) { Upload(member_name, glm::value_ptr(vec)); }
void UniformBuffer::Upload(const std::string& member_name, const glm::vec4& vec) { Upload(member_name, glm::value_ptr(vec)); }
void UniformBuffer::Upload(const std::string& member_name, const glm::mat4& matrix) { Upload(member_name, glm::value_ptr(matrix)); }

void UniformBuffer::Upload(size_t member_index, float f) { Upload(member_index, &f); }
void UniformBuffer::Upload(size_t member_index, const glm::vec2& vec) { Upload(member_index, glm::value_ptr(vec)); }
void UniformBuffer::Upload(size_t member_index, const glm::vec3& vec) { Upload(member_index, glm::value_ptr(vec)); }
void UniformBuffer::Upload(size_t member_index, const glm::vec4& vec) { Upload(member_index, glm::value_ptr(vec)); }
void UniformBuffer::Upload(size_t member_index, const glm::mat4& matrix) { Upload(member_index, glm::value_ptr(matrix)); }

}

#include "buffer_layout.hh"

namespace Delta {

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& buffer_elements) : buffer_elements_(buffer_elements) {
  CalculateOffsetsAndSize();
}

BufferLayout::BufferLayout(const std::vector<BufferElement>& buffer_elements) : buffer_elements_(buffer_elements) {
  CalculateOffsetsAndSize();
}

void BufferLayout::CalculateOffsetsAndSize() {
  size_t offset = 0;
  for (auto& element : buffer_elements_) {
    element.offset = offset;
    offset += element.size;
    stride_ += element.size;
  }

  for (const auto& element : buffer_elements_) {
    size_ += element.size;
  }
}

}

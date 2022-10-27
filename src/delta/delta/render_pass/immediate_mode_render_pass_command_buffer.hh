#pragma once

#include <cstddef>
#include <type_traits>
#include <vector>

namespace Delta {

class ImmediateModeRenderPassCommandBuffer {
public:
  template <typename T> void Push(const T& t) {
    static_assert(std::is_trivially_copyable<T>::value, "Data must be trivially copyable to be pushed into buffer");
    size_t prev_size = buffer_.size();
    buffer_.resize(prev_size + sizeof(T));
    std::memcpy(buffer_.data() + prev_size, &t, sizeof(T));
  }

  template <typename T> T Pop() {
    static_assert(std::is_trivially_copyable<T>::value, "Data must be trivially copyable to be popped from buffer");
    T t { };
    size_t new_size = buffer_.size() - sizeof(T);
    std::memcpy(&t, buffer_.data() + new_size, sizeof(T));
    buffer_.resize(new_size);
    return t;
  }

  template <typename T> T Extract(size_t& index) const {
    static_assert(std::is_trivially_copyable<T>::value, "Data must be trivially copyable to be extracted from buffer");
    T t { };
    std::memcpy(&t, buffer_.data() + index, sizeof(T));
    index += sizeof(T);
    return t;
  }

  void Clear() {
    buffer_.clear();
  }

  size_t Size() const {
    return buffer_.size();
  }

private:
  std::vector<char> buffer_;
};

}

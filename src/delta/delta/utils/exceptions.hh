#pragma once

#include <stdexcept>

namespace Delta {

class InstanceCreateException : public std::runtime_error {
public:
  InstanceCreateException(const char* what = "") : std::runtime_error(what) { }
};

}

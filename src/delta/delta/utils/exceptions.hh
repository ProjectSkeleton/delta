#pragma once

#include <stdexcept>

namespace Delta {

class DeltaException : public std::runtime_error {
public:
  DeltaException(const char* what = "") : std::runtime_error(what) { }
};

class InstanceCreateException : public DeltaException {
public:
  InstanceCreateException(const char* what = "") : DeltaException(what) { }
};

class ShaderCreateException : public DeltaException {
public:
  ShaderCreateException(const char* what = "") : DeltaException(what) { }
};

}

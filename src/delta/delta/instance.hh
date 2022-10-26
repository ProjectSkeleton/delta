#pragma once

#include <memory>

#include "delta/backend/backend.hh"
#include "delta/delta/utils/logger.hh"
#include "delta/delta/window.hh"

namespace Delta {

class Instance {
public:
  virtual std::unique_ptr<Window> CreateWindow(const WindowCreateInfo& window_info = {}) = 0;

private:
  Logger logger_;
};

std::unique_ptr<Instance> CreateInstance(Backend preferred_backend = Backend::kNone);

}

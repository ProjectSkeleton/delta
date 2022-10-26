#pragma once

#include <memory>

#include "delta/backend/backend.hh"
#include "delta/delta/window.hh"

namespace Delta {

class Instance {
public:
  virtual std::unique_ptr<Window> CreateWindow() = 0;
};

}

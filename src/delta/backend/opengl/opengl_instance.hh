#pragma once

#include "delta/delta/instance.hh"

namespace Delta {

class OpenGlInstance : public Instance {
public:
  OpenGlInstance();

  virtual std::unique_ptr<Window> CreateWindow() override;
};

}

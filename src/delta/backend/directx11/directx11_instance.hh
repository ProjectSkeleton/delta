#pragma once

#include "delta/delta/instance.hh"

namespace Delta {

class DirectX11Instance : public Instance {
public:
  virtual std::unique_ptr<Window> CreateWindow() override;
};

}

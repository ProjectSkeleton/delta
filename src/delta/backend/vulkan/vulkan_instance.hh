#pragma once

#include "delta/delta/instance.hh"

namespace Delta {

class VulkanInstance : public Instance {
public:
  virtual std::unique_ptr<Window> CreateWindow() override;
};

}

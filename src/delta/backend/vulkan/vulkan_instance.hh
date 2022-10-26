#pragma once

#include "delta/delta/instance.hh"

namespace Delta {

class VulkanInstance : public Instance {
public:
  VulkanInstance();

  virtual std::unique_ptr<Window> CreateWindow(const WindowCreateInfo& window_info) override;
};

}

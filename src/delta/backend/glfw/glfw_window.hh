#pragma once

#include "delta/delta/window.hh"

namespace Delta {

class GlfwWindow : public Window {
public:
  virtual bool IsOpen() const override;
};

}

#pragma once

#include "delta/delta/window.hh"

namespace Delta {

class WindowsWindow : public Window {
public:
  virtual bool IsOpen() const override;
};

}

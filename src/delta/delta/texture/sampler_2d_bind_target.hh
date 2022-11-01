#pragma once

namespace Delta {

class Sampler2dBindTarget {
public:
  virtual bool IsFrameBuffer() const = 0;
};

}

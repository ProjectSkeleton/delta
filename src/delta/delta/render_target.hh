#pragma once

namespace Delta {

class RenderTarget {
public:
  virtual void OnRenderPassBegin() = 0;
  virtual void OnRenderPassComplete() = 0;
};

}

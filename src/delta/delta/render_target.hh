#pragma once

#include <functional>

namespace Delta {

struct RenderPassInfo;

typedef std::function<void(int width, int height)> RenderTargetResizeCallback;

class RenderTarget {
public:
  virtual void OnRenderPassBegin(const RenderPassInfo& render_pass_info) = 0;
  virtual void OnRenderPassComplete(const RenderPassInfo& render_pass_info) = 0;

  virtual void SetResizeCallback(RenderTargetResizeCallback callback) = 0;
};

}

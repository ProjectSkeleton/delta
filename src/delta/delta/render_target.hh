#pragma once

namespace Delta {

struct RenderPassInfo;

class RenderTarget {
public:
  virtual void OnRenderPassBegin(const RenderPassInfo& render_pass_info) = 0;
  virtual void OnRenderPassComplete(const RenderPassInfo& render_pass_info) = 0;
};

}

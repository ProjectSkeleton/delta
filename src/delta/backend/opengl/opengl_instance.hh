#pragma once

#include "delta/delta/instance.hh"

namespace Delta {

class OpenGlInstance : public Instance {
public:
  virtual std::shared_ptr<Window> CreateWindow(const WindowCreateInfo& window_info) override;
  virtual std::shared_ptr<RenderPass> CreateRenderPass(const std::shared_ptr<RenderTarget>& render_target) override;
  virtual std::shared_ptr<Shader> CreateShader(const ShaderCreateInfo& shader_info) override;
};

}

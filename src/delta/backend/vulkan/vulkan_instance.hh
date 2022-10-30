#pragma once

#include "delta/delta/instance.hh"

namespace Delta {

class VulkanInstance : public Instance {
public:
  VulkanInstance();

  virtual std::shared_ptr<Window> CreateWindow(const WindowCreateInfo& window_info) override;
  virtual std::shared_ptr<RenderPass> CreateRenderPass(const std::shared_ptr<RenderTarget>& render_target) override;
  virtual std::shared_ptr<Shader> CreateShader(const ShaderCreateInfo& shader_info) override;
  virtual std::shared_ptr<Mesh> CreateMesh(const MeshCreateInfo& mesh_info) override;

  virtual std::shared_ptr<Texture> CreateTexture(const TextureInfo& texture_info) override;
  virtual std::shared_ptr<Texture> CreateTexture(const std::string& path) override;
  virtual std::shared_ptr<Texture> CreateTexture(const BlankTextureInfo& blank_texture_info) override;
};

}

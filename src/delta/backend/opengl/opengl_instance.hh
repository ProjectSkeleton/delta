#pragma once

#include "delta/delta/instance.hh"

namespace Delta {

class OpenGlInstance : public Instance {
public:
  virtual std::shared_ptr<Window> CreateWindow(const WindowInfo& window_info) override;
  virtual std::shared_ptr<RenderPass> CreateRenderPass(const RenderPassInfo& render_pass_info) override;
  virtual std::shared_ptr<Shader> CreateShader(const ShaderInfo& shader_info) override;
  virtual std::shared_ptr<Mesh> CreateMesh(const MeshInfo& mesh_info) override;
  virtual std::shared_ptr<FrameBuffer> CreateFrameBuffer(const FrameBufferInfo& texture_info) override;
  virtual std::shared_ptr<Texture> CreateTexture(const std::string& path) override;
  virtual std::shared_ptr<Texture> CreateTexture(const TextureInfo& texture_info) override;
  virtual std::shared_ptr<Texture> CreateTexture(const BlankTextureInfo& blank_texture_info) override;
};

}

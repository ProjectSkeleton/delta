#pragma once

#include "delta/delta/instance.hh"

namespace Delta {

class DirectX11Instance : public Instance {
public:
  DirectX11Instance();

public:
  virtual std::shared_ptr<Window> CreateWindow(const WindowInfo& window_info) override;
  virtual std::shared_ptr<RenderPass> CreateRenderPass(const RenderPassInfo& render_pass_info) override;
  virtual std::shared_ptr<Shader> CreateShader(const ShaderInfo& shader_info) override;
  virtual std::shared_ptr<Mesh> CreateMesh(const MeshInfo& mesh_info) override;

  virtual std::shared_ptr<FrameBuffer> CreateFrameBuffer(const FrameBufferInfo& texture_info) override;

  virtual std::shared_ptr<Texture2d> CreateTexture2d(const std::string& path) override;
  virtual std::shared_ptr<Texture2d> CreateTexture2d(const Texture2dInfo& texture_info) override;
  virtual std::shared_ptr<Texture2d> CreateTexture2d(const BlankTexture2dInfo& blank_texture_info) override;
  virtual std::shared_ptr<Texture2d> CreateTexture2d(const Color& color) override;
};

}

#pragma once

#include <memory>

#include "delta/backend/backend.hh"
#include "delta/delta/render_pass/render_pass.hh"
#include "delta/delta/model/mesh.hh"
#include "delta/delta/shader/shader.hh"
#include "delta/delta/texture/texture.hh"
#include "delta/delta/utils/logger.hh"
#include "delta/delta/window.hh"

namespace Delta {

class Instance {
public:
  virtual std::shared_ptr<Window> CreateWindow(const WindowCreateInfo& window_info = {}) = 0;
  virtual std::shared_ptr<RenderPass> CreateRenderPass(const std::shared_ptr<RenderTarget>& render_target) = 0;
  virtual std::shared_ptr<Shader> CreateShader(const ShaderCreateInfo& shader_info) = 0;
  virtual std::shared_ptr<Mesh> CreateMesh(const MeshCreateInfo& mesh_info) = 0;

  virtual std::shared_ptr<Texture> CreateTexture(const TextureInfo& texture_info) = 0;
  virtual std::shared_ptr<Texture> CreateTexture(const std::string& path) = 0;
  virtual std::shared_ptr<Texture> CreateTexture(const BlankTextureInfo& blank_texture_info) = 0;

private:
  Logger logger_;
};

std::shared_ptr<Instance> CreateInstance(Backend preferred_backend = Backend::kNone);

}

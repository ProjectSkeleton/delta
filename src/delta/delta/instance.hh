#pragma once

#include <memory>

#include "delta/backend/backend.hh"
#include "delta/delta/render_pass/render_pass.hh"
#include "delta/delta/model/mesh.hh"
#include "delta/delta/shader/shader.hh"
#include "delta/delta/texture/frame_buffer.hh"
#include "delta/delta/texture/texture_2d.hh"
#include "delta/delta/utils/logger.hh"
#include "delta/delta/window.hh"

namespace Delta {

class Instance {
public:
  virtual std::shared_ptr<Window> CreateWindow(const WindowInfo& window_info = { }) = 0;
  virtual std::shared_ptr<RenderPass> CreateRenderPass(const RenderPassInfo& render_pass_info) = 0;
  virtual std::shared_ptr<Shader> CreateShader(const ShaderInfo& shader_info) = 0;
  virtual std::shared_ptr<Mesh> CreateMesh(const MeshInfo& mesh_info) = 0;

  virtual std::shared_ptr<FrameBuffer> CreateFrameBuffer(const FrameBufferInfo& frame_buffer_info = { }) = 0;

  virtual std::shared_ptr<Texture2d> CreateTexture2d(const std::string& path) = 0;
  virtual std::shared_ptr<Texture2d> CreateTexture2d(const Texture2dInfo& texture_info) = 0;
  virtual std::shared_ptr<Texture2d> CreateTexture2d(const BlankTexture2dInfo& blank_texture_info) = 0;

private:
  Logger logger_;
};

std::shared_ptr<Instance> CreateInstance(Backend preferred_backend = Backend::kNone);

}

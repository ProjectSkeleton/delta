#include "opengl_instance.hh"

#include "delta/backend/opengl/opengl_frame_buffer.hh"
#include "delta/backend/opengl/opengl_render_pass.hh"
#include "delta/backend/opengl/opengl_mesh.hh"
#include "delta/backend/opengl/opengl_shader.hh"
#include "delta/backend/opengl/opengl_texture.hh"
#include "delta/backend/opengl/opengl_window.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

std::shared_ptr<Window> OpenGlInstance::CreateWindow(const WindowInfo& window_info) {
  return std::make_shared<OpenGlWindow>(window_info);
}

std::shared_ptr<RenderPass> OpenGlInstance::CreateRenderPass(const RenderPassInfo& render_target) {
  return std::make_shared<OpenGlRenderPass>(render_target);
}

std::shared_ptr<Shader> OpenGlInstance::CreateShader(const ShaderInfo& shader_info) {
  return std::make_shared<OpenGlShader>(shader_info);
}

std::shared_ptr<Mesh> OpenGlInstance::CreateMesh(const MeshInfo& mesh_info) {
  return std::make_shared<OpenGlMesh>(mesh_info);
}

std::shared_ptr<FrameBuffer> OpenGlInstance::CreateFrameBuffer(const FrameBufferInfo& frame_buffer_info) {
  return std::make_shared<OpenGlFrameBuffer>(frame_buffer_info);
}

std::shared_ptr<Texture> OpenGlInstance::CreateTexture(const std::string& path) {
  return std::make_shared<OpenGlTexture>(path);
}

std::shared_ptr<Texture> OpenGlInstance::CreateTexture(const TextureInfo& texture_info) {
  return std::make_shared<OpenGlTexture>(texture_info);
}

std::shared_ptr<Texture> OpenGlInstance::CreateTexture(const BlankTextureInfo& blank_texture_info) {
  return std::make_shared<OpenGlTexture>(blank_texture_info);
}

}

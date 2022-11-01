#include "metal_instance.hh"

#include "delta/delta/utils/exceptions.hh"

namespace Delta {

MetalInstance::MetalInstance() {
  throw InstanceCreateException("Metal not yet supported");
}

std::shared_ptr<Window> MetalInstance::CreateWindow(const WindowInfo& window_info) {
  return nullptr;
}

std::shared_ptr<RenderPass> MetalInstance::CreateRenderPass(const RenderPassInfo& render_pass_info) {
  return nullptr;
}

std::shared_ptr<Shader> MetalInstance::CreateShader(const ShaderInfo& shader_info) {
  return nullptr;
}

std::shared_ptr<Mesh> MetalInstance::CreateMesh(const MeshInfo& mesh_info) {
  return nullptr;
}

std::shared_ptr<FrameBuffer> MetalInstance::CreateFrameBuffer(const FrameBufferInfo& frame_buffer_info) {
  return nullptr;
}

std::shared_ptr<Texture> MetalInstance::CreateTexture(const std::string& path) {
  return nullptr;
}

std::shared_ptr<Texture> MetalInstance::CreateTexture(const TextureInfo& texture_info) {
  return nullptr;
}

std::shared_ptr<Texture> MetalInstance::CreateTexture(const BlankTextureInfo& blank_texture_info) {
  return nullptr;
}

}

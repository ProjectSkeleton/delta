#include "opengl_instance.hh"

#include "delta/backend/opengl/opengl_render_pass.hh"
#include "delta/backend/opengl/opengl_window.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

std::shared_ptr<Window> OpenGlInstance::CreateWindow(const WindowCreateInfo& window_info) {
  return std::make_shared<OpenGlWindow>(window_info);
}

std::shared_ptr<RenderPass> OpenGlInstance::CreateRenderPass(const std::shared_ptr<RenderTarget>& render_target) {
  return std::make_shared<OpenGlRenderPass>(render_target);
}

}

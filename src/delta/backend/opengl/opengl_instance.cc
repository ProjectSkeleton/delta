#include "opengl_instance.hh"

#include "delta/backend/opengl/opengl_window.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

OpenGlInstance::OpenGlInstance() {
}

std::unique_ptr<Window> OpenGlInstance::CreateWindow(const WindowCreateInfo& window_info) {
  return std::move(std::make_unique<OpenGlWindow>(window_info));
}

}

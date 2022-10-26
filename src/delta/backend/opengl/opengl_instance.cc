#include "opengl_instance.hh"

#include "delta/backend/opengl/opengl_window.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

OpenGlInstance::OpenGlInstance() {
  throw InstanceCreateException("OpenGl not yet supported");
}

std::unique_ptr<Window> OpenGlInstance::CreateWindow() {
  return std::move(std::make_unique<OpenGlWindow>());
}

}

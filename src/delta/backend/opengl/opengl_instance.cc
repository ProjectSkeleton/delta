#include "opengl_instance.hh"

#include "delta/backend/opengl/opengl_window.hh"

namespace Delta {

std::unique_ptr<Window> OpenGlInstance::CreateWindow() {
  return std::move(std::make_unique<OpenGlWindow>());
}

}

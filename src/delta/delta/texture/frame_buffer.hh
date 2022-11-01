#pragma once

#include <cstddef>

#include "delta/delta/render_target.hh"
#include "delta/delta/texture/texture.hh"

namespace Delta {

struct FrameBufferInfo {
  size_t width = 1;
  size_t height = 1;
  TextureFilter filter = TextureFilter::kNearest;
};

class FrameBuffer : public RenderTarget, public Texture {
public:
  virtual void Resize(unsigned int width, unsigned int height) = 0;
};

}

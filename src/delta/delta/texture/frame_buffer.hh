#pragma once

#include <cstddef>

#include "delta/delta/render_target.hh"
#include "delta/delta/texture/sampler_2d_bind_target.hh"
#include "delta/delta/texture/static_texture.hh"

namespace Delta {

struct FrameBufferInfo {
  size_t width = 1;
  size_t height = 1;
  TextureFilter filter = TextureFilter::kNearest;
};

class FrameBuffer : public RenderTarget, public Sampler2dBindTarget {
public:
  virtual void Resize(unsigned int width, unsigned int height) = 0;

public:
  virtual bool IsFrameBuffer() const override;
};

}

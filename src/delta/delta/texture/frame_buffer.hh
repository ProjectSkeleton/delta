#pragma once

#include <cstddef>

#include "delta/delta/render_target.hh"
#include "delta/delta/texture/texture.hh"

namespace Delta {

struct FrameBufferInfo {
  size_t width;
  size_t height;
};

class FrameBuffer : public RenderTarget, public Texture {
};

}

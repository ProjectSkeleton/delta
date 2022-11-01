#pragma once

#include <cstdint>
#include <string>

#include "delta/delta/color.hh"
#include "delta/delta/texture/sampler_2d_bind_target.hh"
#include "delta/delta/texture/static_texture.hh"

namespace Delta {

struct Texture2dInfo {
  std::string path;
  bool flip_vertical_on_load = false;
  TextureFilter filter = TextureFilter::kLinear;
  TextureWrap wrap = TextureWrap::kRepeat;
};

struct BlankTexture2dInfo {
  uint32_t width = 1;
  uint32_t height = 1;
  Color color;
  TextureFilter filter = TextureFilter::kNearest;
  TextureWrap wrap = TextureWrap::kRepeat;
};

class Texture2d : public StaticTexture, public Sampler2dBindTarget { 
public:
  virtual bool IsFrameBuffer() const override;
};

}

#pragma once

#include <cstdint>

#include "delta/delta/color.hh"

namespace Delta {

enum class TextureWrap {
  kRepeat,
  kMirroredRepeat,
  kClampToEdge,
  kClampToBorder,
};

enum class TextureFilter {
  kLinear,
  kNearest,
};

struct TextureInfo {
  std::string path;
  bool flip_vertical_on_load = false;
  TextureFilter filter = TextureFilter::kLinear;
  TextureWrap wrap = TextureWrap::kRepeat;
};

struct BlankTextureInfo {
  uint32_t width = 1;
  uint32_t height = 1;
  Color color;
  TextureFilter filter = TextureFilter::kLinear;
  TextureWrap wrap = TextureWrap::kRepeat;
};

class Texture {
};

}

#pragma once

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

class StaticTexture { };

}

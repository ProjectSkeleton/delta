#pragma once

#include <cstdint>

namespace Delta {

struct Color {
public:
  Color() = default;
  Color(float r, float g, float b, float a);
  Color(uint32_t color);

public:
  uint32_t UintRgba() const;
  uint32_t UintAbgr() const;

public:
  float r = 1.0f;
  float g = 1.0f;
  float b = 1.0f;
  float a = 1.0f;
};

}

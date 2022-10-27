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

public:
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
  float a = 0.0f;
};

}

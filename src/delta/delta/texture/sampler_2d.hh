#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include "delta/delta/shader/shader_stage.hh"
#include "delta/delta/texture/frame_buffer.hh"
#include "delta/delta/texture/texture_2d.hh"

namespace Delta {

struct Sampler2dInfo {
  uint32_t binding;
  ShaderStage stage;
  std::string name;
};

class Sampler2d {
public:
  Sampler2d(const Sampler2dInfo& sampler_info);

  const std::string& GetName() { return info_.name; };

public:
  virtual void SetTexture(std::shared_ptr<Sampler2dBindTarget> texture) = 0;

protected:
  Sampler2dInfo info_;
};

}

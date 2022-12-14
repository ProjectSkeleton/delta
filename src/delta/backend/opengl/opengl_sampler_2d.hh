#pragma once

#include "delta/delta/texture/sampler_2d.hh"

namespace Delta {

class OpenGlSampler2d : public Sampler2d {
public:
  OpenGlSampler2d(const Sampler2dInfo& sampler_info, unsigned int shader_program, unsigned int texture_slot);

public:
  virtual void SetTexture(std::shared_ptr<Sampler2dBindTarget> texture) override;

public:
  void BindTarget();

private:
  unsigned int shader_program_;
  unsigned int texture_slot_;

  std::shared_ptr<Sampler2dBindTarget> bound_target_;
};

}

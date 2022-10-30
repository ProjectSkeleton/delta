#pragma once

#include "delta/delta/shader/shader.hh"

namespace Delta {

class OpenGlShader : public Shader {
public:
  OpenGlShader(const ShaderCreateInfo& shader_info);
  ~OpenGlShader();

public:
  void Bind() const;

protected:
  virtual void CreateUniformBuffer(const UniformBufferInfo& uniform_info) override;
  virtual void CreateSampler2d(const Sampler2dInfo& sampler_info) override;

private:
  unsigned int shader_program_;
  unsigned int current_texture_slot_ = 0;
};

}

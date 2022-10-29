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
  virtual void CreateUniformBuffer(uint32_t index, const UniformBufferInfo& uniform_info) override;

private:
  unsigned int shader_program_;
};

}

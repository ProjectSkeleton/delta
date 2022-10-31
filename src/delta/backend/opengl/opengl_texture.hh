#pragma once

#include <string>

#include "delta/delta/texture/texture.hh"

namespace Delta {

class OpenGlTexture : public Texture {
public:
  OpenGlTexture(const std::string& path);
  OpenGlTexture(const TextureInfo& texture_info);
  OpenGlTexture(const BlankTextureInfo& blank_texture_info);
  ~OpenGlTexture();

private:
  void CreateTexture(const TextureInfo& texture_info);
  void CreateTexture(int width, int height, int channels, TextureWrap wrap, TextureFilter filter, void* data);

public:
  virtual void Bind() const;

  virtual bool IsFrameBuffer() const override;

private:
  unsigned int texture_;
};

}

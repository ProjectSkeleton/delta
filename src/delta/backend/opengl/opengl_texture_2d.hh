#pragma once

#include <string>

#include "delta/delta/texture/texture_2d.hh"

namespace Delta {

class OpenGlTexture2d : public Texture2d {
public:
  OpenGlTexture2d(const std::string& path);
  OpenGlTexture2d(const Texture2dInfo& texture_info);
  OpenGlTexture2d(const BlankTexture2dInfo& blank_texture_info);
  ~OpenGlTexture2d();

private:
  void CreateTexture(const Texture2dInfo& texture_info);
  void CreateTexture(int width, int height, int channels, TextureWrap wrap, TextureFilter filter, void* data);

public:
  virtual void Bind() const;

private:
  unsigned int texture_;
};

}

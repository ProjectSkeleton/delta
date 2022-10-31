#pragma once

#include "delta/backend/opengl/opengl_texture.hh"
#include "delta/delta/render_pass/render_pass.hh"
#include "delta/delta/texture/frame_buffer.hh"

namespace Delta {

class OpenGlFrameBuffer : public FrameBuffer {
public:
  OpenGlFrameBuffer(const FrameBufferInfo& frame_buffer_info);
  ~OpenGlFrameBuffer();

public:
  virtual void OnRenderPassBegin(const RenderPassInfo& render_pass_info) override;
  virtual void OnRenderPassComplete(const RenderPassInfo& render_pass_info) override;

public:
  virtual void BindAsTexture() const;

  virtual bool IsFrameBuffer() const override;

private:
  unsigned int framebuffer_;
  unsigned int color_attachment_ = 0;
  unsigned int depth_attachment_ = 0;

  size_t width_;
  size_t height_;
};

}

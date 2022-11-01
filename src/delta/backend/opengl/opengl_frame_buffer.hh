#pragma once

#include "delta/backend/opengl/opengl_texture_2d.hh"
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

  virtual void SetResizeCallback(RenderTargetResizeCallback callback) override;

public:
  virtual void Resize(unsigned int width, unsigned int height) override;

public:
  void BindColorAttachment() const;

private:
  unsigned int framebuffer_;
  unsigned int color_attachment_ = 0;
  unsigned int depth_attachment_ = 0;

  int width_;
  int height_;

  RenderTargetResizeCallback resize_callback_;
};

}

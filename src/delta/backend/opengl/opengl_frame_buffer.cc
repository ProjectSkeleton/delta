#include "opengl_frame_buffer.hh"

#include <glad/gl.h>

namespace Delta {

OpenGlFrameBuffer::OpenGlFrameBuffer(const FrameBufferInfo& frame_buffer_info) : width_((int)frame_buffer_info.width), height_((int)frame_buffer_info.height) {
  glGenFramebuffers(1, &framebuffer_);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
  
  // Colour attachment
  glGenTextures(1, &color_attachment_);
  glBindTexture(GL_TEXTURE_2D, color_attachment_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  GLenum filter = frame_buffer_info.filter == TextureFilter::kLinear ? GL_LINEAR : GL_NEAREST;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachment_, 0);
  
  // Depth attachment
  glGenRenderbuffers(1, &depth_attachment_);
  glBindRenderbuffer(GL_RENDERBUFFER, depth_attachment_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_attachment_);
  
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    // TODO: Throw error
  }
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

OpenGlFrameBuffer::~OpenGlFrameBuffer() {
  glDeleteFramebuffers(1, &framebuffer_);
  glDeleteTextures(1, &color_attachment_);
  glDeleteTextures(1, &depth_attachment_);
}

void OpenGlFrameBuffer::OnRenderPassBegin(const RenderPassInfo& render_pass_info) {
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
  glViewport(0, 0, width_, height_);

  if (render_pass_info.enable_depth_test) {
    glEnable(GL_DEPTH_TEST);
  }
  else {
    glDisable(GL_DEPTH_TEST);
  }

  if (render_pass_info.on_begin == RenderPassBeginOp::kClear) {
    glClearColor(render_pass_info.clear_color.r, render_pass_info.clear_color.g, render_pass_info.clear_color.b, render_pass_info.clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
}

void OpenGlFrameBuffer::OnRenderPassComplete(const RenderPassInfo& render_pass_info) {
}

void OpenGlFrameBuffer::Resize(unsigned int width, unsigned int height) {
  width_ = (int)width;
  height_ = (int)height;

  glBindTexture(GL_TEXTURE_2D, color_attachment_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);

  glBindRenderbuffer(GL_RENDERBUFFER, depth_attachment_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void OpenGlFrameBuffer::BindColorAttachment() const {
  glBindTexture(GL_TEXTURE_2D, color_attachment_);
}

}

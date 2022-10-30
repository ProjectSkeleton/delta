#include "opengl_texture.hh"

#include <glad/gl.h>
#include <stb/stb_image.h>

namespace Delta {

GLenum TextureFilterToGLMinFilter(TextureFilter filter) {
  switch (filter) {
    case TextureFilter::kLinear:  return GL_LINEAR_MIPMAP_LINEAR;
    case TextureFilter::kNearest: return GL_NEAREST;
    default:                      return GL_DONT_CARE;
  } 
}
GLenum TextureFilterToGLMagFilter(TextureFilter filter) {
  switch (filter) {
    case TextureFilter::kLinear:  return GL_LINEAR;
    case TextureFilter::kNearest: return GL_NEAREST;
    default:                      return GL_DONT_CARE;
  }
}

GLenum TextureWrapModeToGLEnum(TextureWrap wrap_mode) {
  switch (wrap_mode) {
    case TextureWrap::kRepeat:         return GL_REPEAT;
    case TextureWrap::kMirroredRepeat: return GL_MIRRORED_REPEAT;
    case TextureWrap::kClampToEdge:    return GL_CLAMP_TO_EDGE;
    case TextureWrap::kClampToBorder:  return GL_CLAMP_TO_BORDER;
    default:                           return GL_DONT_CARE;
  }
}

void OpenGlTexture::CreateTexture(int width, int height, int channels, TextureWrap wrap, TextureFilter filter, void* data) {
	GLenum internal_format = 0, data_format = 0;

	if (channels == 4) {
		internal_format = GL_RGBA8;
		data_format = GL_RGBA;
	}
	else if (channels == 3) {
		internal_format = GL_RGB8;
		data_format = GL_RGB;
	}

	// A hack-ish way to void overwriting previous bindings
	// Cache currently bound texture and re-bind it after texture generation is complete
	GLint last_tex;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_tex);
	
	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	GLenum gl_wrap = TextureWrapModeToGLEnum(wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_wrap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToGLMinFilter(filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToGLMagFilter(filter));

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	// Re-bind cached texture
	glBindTexture(GL_TEXTURE_2D, last_tex);
}

void OpenGlTexture::CreateTexture(const TextureInfo& texture_info) {
  int width, height, channels;
	stbi_uc* data = nullptr;

  stbi_set_flip_vertically_on_load(texture_info.flip_vertical_on_load);
	data = stbi_load(texture_info.path.c_str(), &width, &height, &channels, 0);

	CreateTexture(width, height, channels, texture_info.wrap, texture_info.filter, data);

	stbi_image_free(data);
}

OpenGlTexture::OpenGlTexture(const std::string& path) {
	TextureInfo texture_info;
	texture_info.path = path;
	CreateTexture(texture_info);
}

OpenGlTexture::OpenGlTexture(const TextureInfo& texture_info) {
  CreateTexture(texture_info);
}

OpenGlTexture::OpenGlTexture(const BlankTextureInfo& blank_texture_info) {
	size_t data_size = (size_t)blank_texture_info.width * (size_t)blank_texture_info.height;
	uint32_t* data = new uint32_t[data_size];
	// TODO: Why is this backwards?
	uint32_t colour = blank_texture_info.color.UintAbgr();
	for (size_t i = 0; i < data_size; ++i) {
		data[i] = colour;
	}
	
	CreateTexture(blank_texture_info.width, blank_texture_info.height, 4, blank_texture_info.wrap, blank_texture_info.filter, data);

	delete[] data;
}

OpenGlTexture::~OpenGlTexture() {
  glDeleteTextures(1, &texture_);
}

void OpenGlTexture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, texture_);
}

}

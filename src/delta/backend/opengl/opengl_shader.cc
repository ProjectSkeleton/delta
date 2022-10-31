#include "opengl_shader.hh"

#if !defined(NDEBUG)
  #include <sstream>
#endif
#include <memory>
#include <vector>

#include <glad/gl.h>
// spirv-cross is also included with the Vulkan SDK. Make sure not to #include <spirv-cross/spirv_xxx> as this will
// cause mismatched header and cpp files and you will end up with linker errors
#include <spirv_glsl.hpp>

#include "delta/backend/opengl/opengl_sampler_2d.hh"
#include "delta/backend/opengl/opengl_uniform_buffer.hh"
#include "delta/delta/shader/shader_stage.hh"
#include "delta/delta/utils/exceptions.hh"

namespace Delta {

GLenum FindOpenGLShaderStage(ShaderStage stage) {
  switch (stage) {
    case ShaderStage::kFragmentShader: return GL_FRAGMENT_SHADER;
    case ShaderStage::kVertexShader:   return GL_VERTEX_SHADER;
    default: return -1;
  }
}

#if !defined(NDEBUG)
const char* GetShaderStageName(ShaderStage stage) {
  switch (stage) {
    case ShaderStage::kFragmentShader:    return "Fragment Shader";
    case ShaderStage::kVertexShader:      return "Vertex Shader";
    default: return "Unknown Shader Stage";
  }
}
#endif

void ApplyOpenGLCompileOptions(spirv_cross::CompilerGLSL& compiler) {
	spirv_cross::CompilerGLSL::Options options;
  
  std::string glsl_version_str = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
  int version_major, version_minor;
#if defined(_WIN32)
  (void)sscanf_s(glsl_version_str.c_str(), "%d%*c%d", &version_major, &version_minor);
#else
  (void)sscanf(glsl_version_str.c_str(), "%d%*c%d", &version_major, &version_minor);
#endif
  options.version = version_major * 100 + version_minor;

	if (options.version < 420) {
		options.enable_420pack_extension = false;
	}

	options.vertex.flip_vert_y = true;
	compiler.set_common_options(options);
}

GLuint CreateShaderModule(const std::string& glsl_code, ShaderStage shader_stage) {
  GLuint shader;
  shader = glCreateShader(FindOpenGLShaderStage(shader_stage));
	const GLchar* source_ptr = (const GLchar*)glsl_code.c_str();

  glShaderSource(shader, 1, &source_ptr, 0);
  glCompileShader(shader);

#if !defined(NDEBUG)
  GLint is_compiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length = 0;
	  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

	  // max_length includes the null character
	  std::vector<GLchar> info_log(max_length);
	  glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);
	  glDeleteShader(shader);

    std::stringstream exception_msg;
    exception_msg << "Failed to compile " << GetShaderStageName(shader_stage) << ": " << info_log.data();
	  throw ShaderCreateException(exception_msg.str().c_str());
  }
#endif

  return shader;
}

OpenGlShader::OpenGlShader(const ShaderInfo& shader_info) {
  shader_program_ = glCreateProgram();

  auto code_map = LoadSpv(shader_info.spv_paths);

  std::vector<GLuint> shader_modules;
  for (const auto& spv : code_map) {
    spirv_cross::CompilerGLSL compiler(spv.second);
    ApplyOpenGLCompileOptions(compiler);
    const std::string glsl_code = compiler.compile();
		GLuint shader_module = CreateShaderModule(glsl_code, spv.first);
    shader_modules.push_back(shader_module);
	  glAttachShader(shader_program_, shader_module);
  }

  glLinkProgram(shader_program_);

  // Check link status
#if !defined(NDEBUG)
	GLint is_linked = 0;
	glGetProgramiv(shader_program_, GL_LINK_STATUS, &is_linked);
	if (is_linked == GL_FALSE) {
		GLint max_length = 0;
		glGetProgramiv(shader_program_, GL_INFO_LOG_LENGTH, &max_length);
		std::vector<GLchar> info_log(max_length);
		glGetProgramInfoLog(shader_program_, max_length, &max_length, &info_log[0]);
	
		glDeleteProgram(shader_program_);
		for (auto shader : shader_modules) {
			glDeleteShader(shader);
		}

    std::stringstream exception_msg;
    exception_msg << "Failed to link shader: " << info_log.data();
	  throw ShaderCreateException(exception_msg.str().c_str());
		return;
	}
#endif

	// Always detach shaders after a successful link.
	for (auto shader : shader_modules) {
    glDetachShader(shader_program_, shader);
    glDeleteShader(shader);
	}

  glUseProgram(shader_program_);
  PerformReflection(code_map);
  glUseProgram(0);
}

OpenGlShader::~OpenGlShader() {
  glDeleteProgram(shader_program_);
}

void OpenGlShader::Bind() const {
  glUseProgram(shader_program_);
}

void OpenGlShader::CreateUniformBuffer(const UniformBufferInfo& uniform_info) {
  uniform_buffers_.emplace(uniform_info.binding, std::make_shared<OpenGlUniformBuffer>(shader_program_, uniform_info));
}

void OpenGlShader::CreateSampler2d(const Sampler2dInfo& sampler_info) {
  sampler_2ds_.emplace(sampler_info.binding, std::make_shared<OpenGlSampler2d>(sampler_info, shader_program_, current_texture_slot_++));
}

}

cmake_minimum_required(VERSION 3.0)
project(delta)

find_package(Vulkan)

set(DELTA_SRC_FILES
  src/delta/delta.hh
)
source_group("delta/src" FILES ${DELTA_SRC_FILES})

set(DELTA_SRC_BACKEND_FILES
  src/delta/backend/backend.hh
)
source_group("delta/src/backend" FILES ${DELTA_SRC_BACKEND_FILES})

if(WIN32)
  set(DELTA_SRC_BACKEND_DIRECTX11_FILES
    src/delta/backend/directx11/directx11_instance.hh src/delta/backend/directx11/directx11_instance.cc
  )
  source_group("delta/src/backend/directx11" FILES ${DELTA_SRC_BACKEND_DIRECTX11_FILES})
endif()

set(DELTA_SRC_BACKEND_GLFW_FILES
  src/delta/backend/glfw/glfw_window.hh src/delta/backend/glfw/glfw_window.cc
)
source_group("delta/src/backend/glfw" FILES ${DELTA_SRC_BACKEND_GLFW_FILES})

if(APPLE)
  set(DELTA_SRC_BACKEND_METAL_FILES
    src/delta/backend/metal/metal_instance.hh src/delta/backend/metal/metal_instance.cc
  )
  source_group("delta/src/backend/metal" FILES ${DELTA_SRC_BACKEND_METAL_FILES})
endif()

set(DELTA_SRC_BACKEND_OPENGL_FILES
  src/delta/backend/opengl/opengl_instance.hh src/delta/backend/opengl/opengl_instance.cc
  src/delta/backend/opengl/opengl_mesh.hh src/delta/backend/opengl/opengl_mesh.cc
  src/delta/backend/opengl/opengl_render_pass.hh src/delta/backend/opengl/opengl_render_pass.cc
  src/delta/backend/opengl/opengl_shader.hh src/delta/backend/opengl/opengl_shader.cc
  src/delta/backend/opengl/opengl_uniform_buffer.hh src/delta/backend/opengl/opengl_uniform_buffer.cc
  src/delta/backend/opengl/opengl_window.hh src/delta/backend/opengl/opengl_window.cc
)
source_group("delta/src/backend/opengl" FILES ${DELTA_SRC_BACKEND_OPENGL_FILES})

if(Vulkan_FOUND)
  set(DELTA_SRC_BACKEND_VULKAN_FILES
    src/delta/backend/vulkan/vulkan_instance.hh src/delta/backend/vulkan/vulkan_instance.cc
    src/delta/backend/vulkan/vulkan_window.hh src/delta/backend/vulkan/vulkan_window.cc
  )
  source_group("delta/src/backend/vulkan" FILES ${DELTA_SRC_BACKEND_VULKAN_FILES})
endif()

if (WIN32)
  set(DELTA_SRC_BACKEND_WINDOWS_FILES
    src/delta/backend/windows/windows_window.hh src/delta/backend/windows/windows_window.cc
  )
  source_group("delta/src/backend/windows" FILES ${DELTA_SRC_BACKEND_WINDOWS_FILES})
endif()

set(DELTA_SRC_DELTA_FILES
  src/delta/delta/color.hh src/delta/delta/color.cc
  src/delta/delta/instance.hh src/delta/delta/instance.cc
  src/delta/delta/render_target.hh
  src/delta/delta/window.hh
)
source_group("delta/src/delta" FILES ${DELTA_SRC_DELTA_FILES})

set(DELTA_SRC_DELTA_MODEL_FILES
src/delta/delta/model/buffer_element.hh
src/delta/delta/model/buffer_layout.hh src/delta/delta/model/buffer_layout.cc
src/delta/delta/model/mesh.hh
)
source_group("delta/src/delta/model" FILES ${DELTA_SRC_DELTA_MODEL_FILES})

set(DELTA_SRC_DELTA_RENDER_PASS_FILES
  src/delta/delta/render_pass/immediate_mode_render_pass_command_buffer.hh
  src/delta/delta/render_pass/immediate_mode_render_pass.hh src/delta/delta/render_pass/immediate_mode_render_pass.cc
  src/delta/delta/render_pass/render_pass_opcode.hh
  src/delta/delta/render_pass/render_pass.hh
)
source_group("delta/src/delta/render_pass" FILES ${DELTA_SRC_DELTA_RENDER_PASS_FILES})

set(DELTA_SRC_DELTA_SHADER_FILES
  src/delta/delta/shader/shader.hh src/delta/delta/shader/shader.cc
  src/delta/delta/shader/shader_data_type.hh src/delta/delta/shader/shader_data_type.cc
  src/delta/delta/shader/shader_stage.hh
  src/delta/delta/shader/uniform_buffer.hh src/delta/delta/shader/uniform_buffer.cc
)
source_group("delta/src/delta/shader" FILES ${DELTA_SRC_DELTA_SHADER_FILES})

set(DELTA_SRC_DELTA_UTILS_FILES
  src/delta/delta/utils/exceptions.hh
  src/delta/delta/utils/logger.hh src/delta/delta/utils/logger.cc
)
source_group("delta/src/delta/utils" FILES ${DELTA_SRC_DELTA_UTILS_FILES})

add_library(${PROJECT_NAME}
  ${DELTA_SRC_FILES}
  ${DELTA_SRC_BACKEND_FILES}
  ${DELTA_SRC_BACKEND_DIRECTX11_FILES}
  ${DELTA_SRC_BACKEND_GLFW_FILES}
  ${DELTA_SRC_BACKEND_METAL_FILES}
  ${DELTA_SRC_BACKEND_OPENGL_FILES}
  ${DELTA_SRC_BACKEND_VULKAN_FILES}
  ${DELTA_SRC_BACKEND_WINDOWS_FILES}
  ${DELTA_SRC_DELTA_FILES}
  ${DELTA_SRC_DELTA_MODEL_FILES}
  ${DELTA_SRC_DELTA_RENDER_PASS_FILES}
  ${DELTA_SRC_DELTA_SHADER_FILES}
  ${DELTA_SRC_DELTA_UTILS_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC src)

if(Vulkan_FOUND)
  target_compile_definitions(${PROJECT_NAME} PUBLIC DELTA_HAS_VULKAN)
endif()

add_subdirectory(src/depend/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
add_subdirectory(src/depend/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
add_subdirectory(src/depend/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
set(SPIRV_CROSS_CLI OFF CACHE BOOL "Build the CLI binary. Requires SPIRV_CROSS_STATIC." FORCE)
set(SPIRV_CROSS_ENABLE_TESTS OFF CACHE BOOL "Enable SPIRV-Cross tests." FORCE)
set(SPIRV_CROSS_ENABLE_GLSL ON CACHE BOOL "Enable GLSL support." FORCE)
set(SPIRV_CROSS_ENABLE_HLSL OFF CACHE BOOL "Enable HLSL target support." FORCE)
set(SPIRV_CROSS_ENABLE_MSL  OFF CACHE BOOL "Enable MSL target support." FORCE)
set(SPIRV_CROSS_ENABLE_CPP  OFF CACHE BOOL "Enable C++ target support." FORCE)
set(SPIRV_CROSS_ENABLE_REFLECT OFF CACHE BOOL "Enable JSON reflection target support." FORCE)
set(SPIRV_CROSS_ENABLE_C_API OFF CACHE BOOL "Enable C API wrapper support in static library." FORCE)
set(SPIRV_CROSS_ENABLE_UTIL OFF CACHE BOOL "Enable util module support." FORCE)
add_subdirectory(src/depend/SPIRV-Cross)
target_link_libraries(${PROJECT_NAME} PRIVATE spirv-cross-glsl)

if (PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)

  if(APPLE)
    set_target_properties(delta_test PROPERTIES XCODE_GENERATE_SCHEME TRUE XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
    endif()
  if(WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT delta_test)
    set_property(TARGET delta_test PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
  endif()
endif()

cmake_minimum_required(VERSION 3.0)
project(delta_test)

set(DELTA_TEST_SRC_FILES
  main.cc
)
source_group("delta_test/src" FILES ${DELTA_TEST_SRC_FILES})

set(DELTA_TEST_GLSL_FILES
  glsl/entity.vert.glsl
  glsl/entity.frag.glsl
  glsl/final.vert.glsl
  glsl/final.frag.glsl
)
source_group("delta_test/src/glsl" FILES ${DELTA_TEST_GLSL_FILES})

add_executable(${PROJECT_NAME} ${DELTA_TEST_SRC_FILES} ${DELTA_TEST_GLSL_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE delta)

# Add custom target - compile glsl shaders to spirv
set(GLSLANG_VALIDATOR "glslangValidator")
file(GLOB_RECURSE GLSL_SOURCE_FILES "glsl/*.glsl")
foreach(GLSL_FILE ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL_FILE} NAME)
  string(REGEX REPLACE "[.]glsl$" ".spv" SPIRV_FILE_NAME ${FILE_NAME})
  set(SPIRV_FILE "${CMAKE_CURRENT_SOURCE_DIR}/spv/${SPIRV_FILE_NAME}")
  add_custom_command(
    OUTPUT ${SPIRV_FILE}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/spv/"
    COMMAND ${GLSLANG_VALIDATOR} -V ${GLSL_FILE} -o ${SPIRV_FILE}
    DEPENDS ${GLSL_FILE})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV_FILE})
endforeach(GLSL_FILE)
add_custom_target(calcium_test_shader_target DEPENDS ${SPIRV_BINARY_FILES})
add_dependencies(${PROJECT_NAME} calcium_test_shader_target)

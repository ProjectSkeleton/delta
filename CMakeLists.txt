cmake_minimum_required(VERSION 3.0)
project(delta)

set(DELTA_SRC_FILES 
  src/delta/delta.hh src/delta/delta.cc
)
source_group("delta/src" FILES ${DELTA_SRC_FILES})

set(DELTA_SRC_BACKEND_FILES 
  src/delta/backend/backend.hh
)
source_group("delta/src/backend" FILES ${DELTA_SRC_BACKEND_FILES})

add_library(${PROJECT_NAME}
  ${DELTA_SRC_FILES}
  ${DELTA_SRC_BACKEND_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC src)

if (PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)

  if(APPLE)
    set_target_properties(delta_test PROPERTIES XCODE_GENERATE_SCHEME TRUE XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
  if(WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT delta_test)
    set_property(TARGET delta_test PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  endif()
endif()

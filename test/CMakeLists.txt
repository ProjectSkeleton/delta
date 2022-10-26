cmake_minimum_required(VERSION 3.0)
project(delta_test)

set(TEST_SRC_FILES main.cc)
source_group("delta_test/src" FILES ${TEST_SRC_FILES})

add_executable(${PROJECT_NAME} ${TEST_SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE delta)

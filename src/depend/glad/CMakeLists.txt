cmake_minimum_required(VERSION 3.0)
project(glad)

add_library(${PROJECT_NAME} src/gl.c include/glad/gl.h include/KHR/khrplatform.h)
target_include_directories(${PROJECT_NAME} PUBLIC include)

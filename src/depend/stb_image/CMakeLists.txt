cmake_minimum_required(VERSION 3.0)
project(stb_image)

add_library(${PROJECT_NAME} stb/stb_image.c stb/stb_image.h)

target_include_directories(${PROJECT_NAME} PUBLIC .)

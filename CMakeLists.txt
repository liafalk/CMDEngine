cmake_minimum_required(VERSION 3.6)
project(RenderingEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp RenderEngine.cpp RenderEngine.h)
add_executable(RenderingEngine ${SOURCE_FILES})
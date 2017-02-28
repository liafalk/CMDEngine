cmake_minimum_required(VERSION 3.6)
project(RenderEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp RenderEngine/RenderEngine.cpp RenderEngine/RenderEngine.h RenderEngine/sprite.cpp RenderEngine/sprite.h RenderEngine/canvas.cpp RenderEngine/canvas.h RenderEngine/vector2.h)
add_executable(RenderEngine ${SOURCE_FILES})
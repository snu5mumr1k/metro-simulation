cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

project(MetroSimulation CXX)

add_subdirectory(bin)
add_subdirectory(external)
add_subdirectory(lib)
add_subdirectory(proto)
add_subdirectory(shaders)
add_subdirectory(textures)

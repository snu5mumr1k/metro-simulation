cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

message(${CMAKE_MODULE_PATH})

project(MetroSimulation CXX)

add_subdirectory(lib)
add_subdirectory(bin)
add_subdirectory(external)

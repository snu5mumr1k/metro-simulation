add_library(lib-graphics-adapter
    sdl_adapter.cpp
)

include(FindOpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

message(${SDL2_LIBRARY})

target_link_libraries(lib-graphics-adapter
    external-gl
    ${SDL2_LIBRARY}
)

target_include_directories(lib-graphics-adapter
    PUBLIC ${CMAKE_SOURCE_DIR}
)

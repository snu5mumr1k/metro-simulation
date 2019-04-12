include(FindOpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_library(lib-graphics-texture
    texture.cpp
)

target_link_libraries(lib-graphics-texture
    ${SDL2_LIBRARY}
    external-gl
)

target_include_directories(lib-graphics-texture
    PUBLIC ${CMAKE_SOURCE_DIR}
    PRIVATE ${CMAKE_BINARY_DIR}
)

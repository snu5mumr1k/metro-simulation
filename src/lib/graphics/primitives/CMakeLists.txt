include(FindOpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_library(lib-graphics-primitives
    rectangle.cpp
)

target_link_libraries(lib-graphics-primitives
    external-gl
    lib-graphics-shader
    lib-graphics-texture
)

target_include_directories(lib-graphics-primitives
    PUBLIC ${CMAKE_SOURCE_DIR}
    PRIVATE ${CMAKE_BINARY_DIR}
)

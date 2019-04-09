include(FindOpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_library(lib-graphics-shader
    shader.cpp
)

target_link_libraries(lib-graphics-shader
    external-gl
)

target_include_directories(lib-graphics-shader
    PUBLIC ${CMAKE_SOURCE_DIR}
    PRIVATE ${CMAKE_BINARY_DIR}
)

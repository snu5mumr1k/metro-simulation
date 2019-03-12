include(FindOpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_library(lib-graphics-adapter
    sdl_adapter.cpp
)

target_link_libraries(lib-graphics-adapter
    ${SDL2_LIBRARY}
    external-gl
    proto
)

target_include_directories(lib-graphics-adapter
    PUBLIC ${CMAKE_SOURCE_DIR}
    PRIVATE ${CMAKE_BINARY_DIR}
    PRIVATE ${PROTOBUF_LIBRARY}
)

include(FindOpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_library(lib-graphics-interface
    metro_representation.cpp
    config_editor.cpp
    metro_editor.cpp
)

target_link_libraries(lib-graphics-interface
    ${SDL2_LIBRARY}
    external-gl
    lib-graphics-primitives
    lib-util-idgenerator
    proto
)

target_include_directories(lib-graphics-interface
    PUBLIC ${CMAKE_SOURCE_DIR}
    PRIVATE ${CMAKE_BINARY_DIR}
    PRIVATE ${PROTOBUF_LIBRARY}
)

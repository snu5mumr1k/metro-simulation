add_library(lib-util-idgenerator
    id_generator.cpp
)

target_include_directories(lib-util-idgenerator
    PUBLIC ${CMAKE_SOURCE_DIR}
)

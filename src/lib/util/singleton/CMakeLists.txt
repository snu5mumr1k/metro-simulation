add_library(lib-util-singleton
    singleton.cpp
)

target_include_directories(lib-util-singleton
    PUBLIC ${CMAKE_SOURCE_DIR}
)

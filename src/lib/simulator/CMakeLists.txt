add_library(lib-simulator
    simulator.cpp
)

target_link_libraries(lib-simulator
    proto
)

target_include_directories(lib-simulator
    PRIVATE ${PROTOBUF_LIBRARY}
)

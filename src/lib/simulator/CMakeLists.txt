add_library(lib-simulator
    line.cpp
    metro.cpp
    path.cpp
    platform.cpp
    section.cpp
    simulator.cpp
    station.cpp
    train.cpp
)

target_link_libraries(lib-simulator
    proto
)

target_include_directories(lib-simulator
    PUBLIC ${CMAKE_SOURCE_DIR}
    PRIVATE ${PROTOBUF_LIBRARY}
)

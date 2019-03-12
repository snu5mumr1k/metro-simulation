find_package(Protobuf REQUIRED)

protobuf_generate_cpp(
    PROTO_SRCS
    PROTO_HDRS

    config.proto
)

add_library(proto
    ${PROTO_SRCS}
)

target_link_libraries(proto
    PUBLIC ${PROTOBUF_LIBRARY}
)

target_include_directories(proto
    PUBLIC ${PROTOBUF_INCLUDE_DIRS}
    PUBLIC ${CMAKE_BINARY_DIR}
)

target_compile_options(proto
    PUBLIC -DGOOGLE_PROTOBUF_DONT_USE_UNALIGNED
)

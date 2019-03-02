add_executable(metro-simulator
    main.cpp
)
target_include_directories(metro-simulator
    PUBLIC ${CMAKE_SOURCE_DIR}
)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

message(${SDL2_LIBRARY})

target_link_libraries(metro-simulator
    external-gl
    ${SDL2_LIBRARY}
    lib-graphics-adapter
    lib-util-singleton
)

add_subdirectory(gl)

add_library(external-imgui
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp

    imgui/examples/imgui_impl_opengl3.cpp
    imgui/examples/imgui_impl_sdl.cpp
)

target_include_directories(external-imgui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    PRIVATE ${CMAKE_SOURCE_DIR}
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

target_compile_options(external-imgui
    PRIVATE -DIMGUI_IMPL_OPENGL_LOADER_CUSTOM=<external/gl/gl_core_3_3.h>
)

target_link_libraries(external-imgui
    external-gl
    ${SDL2_LIBRARY}
)

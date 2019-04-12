#include "metro_editor.h"

#include <external/imgui/imgui.h>

namespace graphics {
metro_simulation::Metro EditMetro(metro_simulation::Metro metro) {
    ImGui::Begin("Edit Metro");


    ImGui::End();

    return metro;
}
}  // namespace graphics

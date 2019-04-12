#include "config_editor.h"

#include <external/imgui/imgui.h>

namespace graphics {
metro_simulation::Config EditConfig(metro_simulation::Config result) {
    ImGui::Begin("Configuration");

    int32_t frames_per_second = result.frames_per_second();
    ImGui::SliderInt("Frames per second", &frames_per_second, 20, 60);
    result.set_frames_per_second(frames_per_second);

    int32_t ticks_per_frame = result.ticks_per_frame();
    ImGui::SliderInt("Ticks per frame", &ticks_per_frame, 0, 20);
    result.set_ticks_per_frame(ticks_per_frame);

    int64_t tick_simulation_seconds = result.tick_simulation_seconds();
    const int64_t min_simulation_seconds = 1;
    const int64_t max_simulation_seconds = 5;
    ImGui::SliderScalar(
        "Tick duration (in simulation)",
        ImGuiDataType_S64,
        &tick_simulation_seconds,
        &min_simulation_seconds,
        &max_simulation_seconds);
    result.set_tick_simulation_seconds(tick_simulation_seconds);

    ImGui::End();
    return result;
}
}  // namespace graphics

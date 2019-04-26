#include <lib/graphics/interface/config_editor.h>

#include <external/imgui/imgui.h>

namespace graphics {
proto::Config EditConfig(proto::Config result) {
  ImGui::Begin("Configuration");

  int32_t frames_per_second = result.frames_per_second();
  ImGui::SliderInt("Frames per second", &frames_per_second, 1, 60);
  result.set_frames_per_second(frames_per_second);

  int32_t ticks_per_frame = result.ticks_per_frame();
  ImGui::SliderInt("Ticks per frame", &ticks_per_frame, 0, 20);
  result.set_ticks_per_frame(ticks_per_frame);

  double seconds_per_tick = result.seconds_per_tick();
  const auto min_simulation_seconds = 0.;
  const auto max_simulation_seconds = 2.;
  ImGui::SliderScalar(
    "Seconds per tick",
    ImGuiDataType_Double,
    &seconds_per_tick,
    &min_simulation_seconds,
    &max_simulation_seconds);
  result.set_seconds_per_tick(seconds_per_tick);

  ImGui::End();
  return result;
}
}  // namespace graphics

#include "metro_editor.h"

#include <string>

#include <external/imgui/imgui.h>

namespace graphics {
metro_simulation::Metro EditMetro(metro_simulation::Metro metro) {
    ImGui::Begin("Edit Metro");

    ImGui::Text("Lines");

    int64_t max_line_id = -1;
    for (int i = 0; i < metro.lines().size(); ++i) {
        const auto &line = metro.lines(i);
        max_line_id = std::max(max_line_id, line.id());

        ImGui::Button("-");
        ImGui::SameLine();
        const std::string line_header = "Line " + std::to_string(line.id());
        if (ImGui::CollapsingHeader(line_header.c_str())) {
            ImGui::Indent();
            {
                if (line.stations().size() > 0) {
                    if (ImGui::CollapsingHeader("Stations")) {
                        for (const auto &station : line.stations()) {
                            ImGui::Button("-");
                            ImGui::SameLine();
                            ImGui::Text("Id %lld", station.id());
                            for (const auto &platform : station.platforms()) {
                                ImGui::BulletText("Platform %lld", platform.id());
                            }
                        }
                    }
                } else {
                    ImGui::Button("+");
                    ImGui::SameLine();
                    ImGui::Text("No stations");
                }
                if (line.sections().size() > 0) {
                    if (ImGui::CollapsingHeader("Sections")) {
                        for (const auto &section : line.sections()) {
                            ImGui::Button("-");
                            ImGui::SameLine();
                            ImGui::Text("Id %lld", section.id());
                        }
                    }
                } else {
                    ImGui::Button("+");
                    ImGui::SameLine();
                    ImGui::Text("No sections");
                }
            }
            ImGui::Unindent();
        }

        ImGui::Separator();
    }

    if (ImGui::Button("+")) {
        auto new_line = metro.add_lines();
        new_line->set_id(max_line_id + 1);
    }

    ImGui::End();

    return metro;
}
}  // namespace graphics

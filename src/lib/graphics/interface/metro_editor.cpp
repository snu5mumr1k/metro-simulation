#include "metro_editor.h"

#include <string>

#include <external/imgui/imgui.h>

namespace graphics {
metro_simulation::Metro EditMetro(metro_simulation::Metro metro) {
    static bool currently_editing_line = false;
    static int64_t new_line_index = -1;

    ImGui::Begin("Edit Metro");

    if (currently_editing_line) {
        ImGui::Text("Line id: %lld", metro.lines(new_line_index).id());

        if (ImGui::Button("Save")) {
            currently_editing_line = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Delete")) {
            auto lines = metro.mutable_lines();
            lines->SwapElements(new_line_index, metro.lines().size() - 1);
            lines->RemoveLast();
            currently_editing_line = false;
        }
    } else {
        ImGui::Text("Lines");

        int64_t max_line_id = -1;
        std::vector<int64_t> to_delete;
        for (int i = 0; i < metro.lines().size(); ++i) {
            const auto &line = metro.lines(i);
            max_line_id = std::max(max_line_id, line.id());

            const std::string line_header = "Line " + std::to_string(line.id());
            if (ImGui::CollapsingHeader(line_header.c_str())) {
                ImGui::Indent();
                {
                    if (ImGui::CollapsingHeader("Stations")) {
                        for (const auto &station : line.stations()) {
                            ImGui::Text("Id %lld", station.id());
                            for (const auto &platform : station.platforms()) {
                                ImGui::BulletText("Platform %lld", platform.id());
                            }
                        }
                    }
                    if (ImGui::CollapsingHeader("Sections")) {
                        for (const auto &section : line.sections()) {
                            ImGui::Text("Id %lld", section.id());
                        }
                    }
                }
                if (!currently_editing_line) {
                    currently_editing_line = ImGui::Button("Edit");
                    if (currently_editing_line) {
                        new_line_index = i;
                    }
                }
                ImGui::Unindent();
            }
        }

        ImGui::Separator();

        if (!currently_editing_line) {
            currently_editing_line = ImGui::Button("Add new line");
            if (currently_editing_line) {
                auto new_line = metro.add_lines();
                new_line->set_id(max_line_id + 1);
                new_line_index = metro.lines().size() - 1;
            }
        }
    }

    ImGui::End();

    return metro;
}
}  // namespace graphics

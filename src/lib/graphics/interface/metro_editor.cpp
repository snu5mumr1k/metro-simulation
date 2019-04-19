#include "metro_editor.h"

#include <string>

#include <external/imgui/imgui.h>

namespace graphics {
proto::Metro EditMetro(proto::Metro metro) {
    ImGui::Begin("Edit Metro");

    ImGui::Text("Lines");

    int64_t max_line_id = -1;
    for (int i = 0; i < metro.lines().size(); ++i) {
        const auto &line = metro.lines(i);
        max_line_id = std::max(max_line_id, line.id());

        if (ImGui::Button("-##line")) {
            metro.mutable_lines()->SwapElements(i, metro.lines().size() - 1);
            metro.mutable_lines()->RemoveLast();
            i--;
            continue;
        }
        ImGui::SameLine();
        const std::string line_header = "Line " + std::to_string(line.id());
        if (ImGui::CollapsingHeader(line_header.c_str())) {
            ImGui::Indent();
            if (ImGui::CollapsingHeader("Stations")) {
                int64_t max_station_id = -1;
                for (int j = 0; j < line.stations().size(); ++j) {
                    const auto &station = line.stations(j);
                    max_station_id = std::max(max_station_id, station.id());

                    if (ImGui::Button("-##station")) {
                        auto stations = metro.mutable_lines(i)->mutable_stations();
                        stations->SwapElements(j, stations->size() - 1);
                        stations->RemoveLast();
                        j--;
                        continue;
                    }
                    ImGui::SameLine();
                    ImGui::Text("Station %lld", station.id());
                    ImGui::Indent();
                    for (const auto &platform : station.platforms()) {
                        ImGui::BulletText("Platform %lld", platform.id());
                    }
                    ImGui::Unindent();
                }
                if (ImGui::Button("+##station")) {
                    auto new_station = metro.mutable_lines(i)->add_stations();
                    new_station->set_id(max_station_id + 1);
                    new_station->add_platforms()->set_id(0);
                    new_station->add_platforms()->set_id(1);
                }
            }
            if (ImGui::CollapsingHeader("Sections")) {
                int64_t max_section_id = -1;
                for (int j = 0; j < line.sections().size(); ++j) {
                    const auto &section = line.sections(j);
                    max_section_id = std::max(max_section_id, section.id());
                    if (ImGui::Button("-##section")) {
                        auto sections = metro.mutable_lines(i)->mutable_sections();
                        sections->SwapElements(j, line.sections().size() - 1);
                        sections->RemoveLast();
                        j--;
                        continue;
                    }
                    ImGui::SameLine();
                    ImGui::Text("Section %lld", section.id());
                    ImGui::SameLine();
                    ImGui::Text("From %lld to %lld", section.origin_platform_id(), section.destination_platform_id());
                }
                static int64_t origin_platform_id = 0;
                static int64_t destination_platform_id = 0;
                ImGui::InputScalar("From##section", ImGuiDataType_S64, &origin_platform_id);
                ImGui::SameLine();
                ImGui::InputScalar("To##section", ImGuiDataType_S64, &destination_platform_id);
                if (ImGui::Button("+##section")) {
                    auto new_section = metro.mutable_lines(i)->add_sections();
                    new_section->set_id(max_section_id + 1);
                    new_section->set_origin_platform_id(origin_platform_id);
                    new_section->set_destination_platform_id(destination_platform_id);
                }
            }
            ImGui::Unindent();
        }

        ImGui::Separator();
    }

    if (ImGui::Button("+##line")) {
        auto new_line = metro.add_lines();
        new_line->set_id(max_line_id + 1);
    }

    ImGui::End();

    return metro;
}
}  // namespace graphics

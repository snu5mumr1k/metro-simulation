#include "metro_editor.h"

#include <lib/util/singleton/singleton.h>
#include <lib/util/id_generator/id_generator.h>

#include <external/imgui/imgui.h>

#include <string>

#include <iostream>
namespace graphics {
proto::Metro EditMetro(proto::Metro metro) {
    ImGui::Begin("Edit Metro");

    ImGui::Text("Lines");

    for (int i = 0; i < metro.lines().size(); ++i) {
        const auto &line = metro.lines(i);

        const std::string button_id = "-##line" + std::to_string(line.id());
        if (ImGui::Button(button_id.c_str())) {
            metro.mutable_lines()->SwapElements(i, metro.mutable_lines()->size() - 1);
            metro.mutable_lines()->RemoveLast();
            i--;
            continue;
        }
        ImGui::SameLine();
        const std::string line_header = "Line " + std::to_string(line.id());
        if (ImGui::CollapsingHeader(line_header.c_str())) {
            ImGui::Indent();
            if (ImGui::CollapsingHeader("Stations")) {
                for (int j = 0; j < line.stations().size(); ++j) {
                    const auto &station = line.stations(j);

                    const std::string button_id = "-##station" + std::to_string(station.id());
                    if (ImGui::Button(button_id.c_str())) {
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
                    new_station->set_id(util::Singleton<util::IdGenerator<proto::Station>>()->GenerateNewId());
                    new_station->add_platforms()->set_id(util::Singleton<util::IdGenerator<proto::Platform>>()->GenerateNewId());
                    new_station->add_platforms()->set_id(util::Singleton<util::IdGenerator<proto::Platform>>()->GenerateNewId());
                }
            }
            if (ImGui::CollapsingHeader("Sections")) {
                for (int j = 0; j < line.sections().size(); ++j) {
                    const auto &section = line.sections(j);
                    const std::string button_id = "-##section" + std::to_string(section.id());
                    if (ImGui::Button(button_id.c_str())) {
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
                    new_section->set_id(util::Singleton<util::IdGenerator<proto::Section>>()->GenerateNewId());
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
        new_line->set_id(util::Singleton<util::IdGenerator<proto::Line>>()->GenerateNewId());
    }

    ImGui::End();

    return metro;
}
}  // namespace graphics

#include "metro_representation.h"

#include <external/imgui/imgui.h>

namespace graphics {
void GenerateTextMetroRepresentation(const metro_simulation::Metro &metro) {
    std::unordered_map<int64_t, std::vector<const metro_simulation::Train *>> sectionsTrains;
    std::unordered_map<int64_t, std::vector<const metro_simulation::Train *>> platformsTrains;
    for (const auto &line : metro.lines()) {
        for (const auto &train : line.trains()) {
            switch (train.state()) {
                case metro_simulation::Train::SECTION: {
                    sectionsTrains[train.section_id()].push_back(&train);
                    break;
                }
                case metro_simulation::Train::PLATFORM: {
                    platformsTrains[train.section_id()].push_back(&train);
                    break;
                }
                default:
                    break;
            }
        }
    }

    ImGui::Begin("Train positions");
    for (const auto &line : metro.lines()) {
        ImGui::Text("Line %lld", line.id());
        for (const auto &section : line.sections()) {
            ImGui::Text("Section %lld", section.id());
            for (const auto *train : sectionsTrains[section.id()]) {
                ImGui::Text("Train %lld completed %lld/%lld", train->id(), train->section_completed_meters(), section.length());
            }
        }
        for (const auto &station : line.stations()) {
            ImGui::Text("Station %lld", station.id());
            for (const auto &platform : station.platforms()) {
                for (const auto *train : platformsTrains[platform.id()]) {
                    ImGui::Text("Train %lld is at the platform %lld", train->id(), platform.id());
                }
            }
        }
        for (const auto &train : line.trains()) {
            if (train.state() == metro_simulation::Train::IDLE) {
                ImGui::Text("Train %lld is idle at %lld", train.id(), train.platform_id());
            }
        }
    }
    ImGui::End();
}
}  // namespace graphics

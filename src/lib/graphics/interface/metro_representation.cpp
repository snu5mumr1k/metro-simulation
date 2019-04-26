#include <lib/graphics/interface/metro_representation.h>

#include <external/imgui/imgui.h>

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace graphics {
void GenerateTextMetroRepresentation(const proto::Metro &metro) {
  std::unordered_map<int64_t, std::vector<const proto::Train *>> sections_trains;
  std::unordered_map<int64_t, std::vector<const proto::Train *>> platform_trains;
  for (const auto &line : metro.lines()) {
    for (const auto &train : line.trains()) {
      switch (train.state()) {
        case proto::Train::SECTION: {
          sections_trains[train.section_id()].push_back(&train);
          break;
        }
        case proto::Train::PLATFORM: {
          platform_trains[train.section_id()].push_back(&train);
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
      std::string description = "%lld " + std::string(40, '.') + " %lld";
      for (const auto *train : sections_trains[section.id()]) {
        const auto length = description.size();
        const auto completed_part = train->section_completed_meters() * length / section.length();
        description[completed_part % length] = '=';
      }
      ImGui::Text(description.c_str(), section.origin_platform_id(), section.destination_platform_id());
    }
    for (const auto &station : line.stations()) {
      for (const auto &platform : station.platforms()) {
        for (const auto *train : platform_trains[platform.id()]) {
          ImGui::Text("Train %lld is at the platform %lld", train->id(), platform.id());
        }
      }
    }
    for (const auto &train : line.trains()) {
      std::map<int64_t, int64_t> ordered_path;
      for (const auto &p : train.path().next_step()) {
        ordered_path[p.first] = p.second;
      }
      if (train.state() == proto::Train::IDLE) {
        ImGui::Text("Train %lld is idle at %lld", train.id(), train.platform_id());
      }
    }
  }
  ImGui::End();
}
}  // namespace graphics

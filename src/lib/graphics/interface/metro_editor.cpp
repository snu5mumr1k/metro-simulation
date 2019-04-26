#include <lib/graphics/interface/metro_editor.h>

#include <lib/util/singleton/singleton.h>
#include <lib/util/id_generator/id_generator.h>

#include <external/imgui/imgui.h>

#include <string>
#include <map>
#include <unordered_map>

namespace {
void EditLines(proto::Metro &metro) {
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
        new_station->add_platforms()->set_id(
          util::Singleton<util::IdGenerator<proto::Platform>>()->GenerateNewId());
        new_station->add_platforms()->set_id(
          util::Singleton<util::IdGenerator<proto::Platform>>()->GenerateNewId());
      }
      }
      if (ImGui::CollapsingHeader("Sections")) {
        for (int j = 0; j < line.sections().size(); ++j) {
          const auto &section = line.sections(j);
          metro.mutable_lines(i)->mutable_sections(j)->set_length(1200);
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
          ImGui::Text(
          "From %lld to %lld with length %lld",
            section.origin_platform_id(),
            section.destination_platform_id(),
            section.length());
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
}

void EditTrains(proto::Metro &metro) {
  ImGui::Separator();
  ImGui::Spacing();
  ImGui::Text("Trains");

  for (int i = 0; i < metro.lines().size(); ++i) {
    auto line = metro.mutable_lines(i);
    const std::string line_header = "Line##" + std::to_string(line->id());
    if (ImGui::CollapsingHeader(line_header.c_str())) {
      for (int j = 0; j < line->trains().size(); ++j) {
        ImGui::Indent();
        auto train = line->mutable_trains(j);
        const std::string button_id = "-##" + std::to_string(train->id());
        if (ImGui::Button(button_id.c_str())) {
          line->mutable_trains()->SwapElements(j, line->mutable_trains()->size() - 1);
          line->mutable_trains()->RemoveLast();
          j--;
          continue;
        }
        ImGui::SameLine();
        const std::string train_header = "Train##" + std::to_string(train->id());
        if (ImGui::CollapsingHeader(train_header.c_str())) {
          ImGui::Indent();
          auto &path = *train->mutable_path();
          std::unordered_map<int64_t, int64_t> previous_step;
          std::map<int64_t, int64_t> ordered_path;
          for (const auto &p : path.next_step()) {
            const auto current_section = p.first;
            const auto next_section = p.second;
            previous_step[next_section] = current_section;
            ordered_path[current_section] = next_section;
          }

          for (const auto &p : ordered_path) {
            const auto current_section = p.first;
            const auto next_section = p.second;
            const std::string button_id = "-##"
              + std::to_string(current_section)
              + std::to_string(next_section);
            if (ImGui::Button(button_id.c_str())) {
              path.mutable_next_step()->erase(current_section);
              path.mutable_next_step()->erase(previous_step[current_section]);
              path.mutable_next_step()->insert({previous_step[current_section], next_section});
              break;
            }
            ImGui::SameLine();
            ImGui::Text("%lld -> %lld", current_section, next_section);
          }
          static int64_t current_section = 0;
          static int64_t next_section = 0;
          ImGui::InputScalar("Current section##path", ImGuiDataType_S64, &current_section);
          ImGui::SameLine();
          ImGui::InputScalar("Next section##path", ImGuiDataType_S64, &next_section);
          if (ImGui::Button("+##path")) {
            path.mutable_next_step()->insert({current_section, next_section});
          }
          ImGui::Unindent();
        }
      }
      if (ImGui::Button("+##train")) {
        auto new_train = line->add_trains();
        new_train->set_id(util::Singleton<util::IdGenerator<proto::Train>>()->GenerateNewId());
      }
      ImGui::Unindent();
    }
  }
}
}  // namespace

namespace graphics {
proto::Metro EditMetro(proto::Metro metro) {
  ImGui::Begin("Edit Metro");

  ImGui::Text("Lines");

  EditLines(metro);
  EditTrains(metro);

  ImGui::End();

  return metro;
}
}  // namespace graphics

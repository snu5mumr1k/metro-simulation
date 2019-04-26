#include <lib/simulator/line.h>

namespace core {
Line::Line(proto::Line *line) : line_(line) {
  for (auto &station : *line->mutable_stations()) {
  stations_.emplace(station.id(), Station(&station));
  for (auto &platform : *station.mutable_platforms()) {
    platforms_.emplace(platform.id(), Platform(&platform));
  }
  }

  for (auto &section : *line->mutable_sections()) {
  sections_.emplace(section.id(), Section(&section));
  }

  for (auto &train : *line->mutable_trains()) {
  trains_.emplace(train.id(), Train(&train, sections_));
  }
}

void Line::Tick(const proto::Config &config) {
  for (auto &[_, train] : trains_) {
  train.Tick(config);
  }
}
}  // namespace core

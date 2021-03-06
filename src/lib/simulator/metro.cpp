#include <lib/simulator/metro.h>

namespace core {
Metro::Metro(proto::Metro *metro) : metro_(metro) {
  for (auto &line : *metro->mutable_lines()) {
    lines_.emplace_back(&line);
  }
}

void Metro::Tick(const proto::Config &config) {
  for (auto &line : lines_) {
    line.Tick(config);
  }
}

void Metro::Refresh() {
  for (auto &line : lines_) {
    line.Refresh();
  }
}

const proto::Metro &Metro::metro() const {
  return *metro_;
}
}  // namespace core

#include "metro.h"

namespace core {
Metro::Metro(metro_simulation::Metro *metro) : metro_(metro) {
    for (auto &line : *metro->mutable_lines()) {
        lines_.emplace_back(&line);
    }
}

void Metro::Tick() {
    for (auto &line : lines_) {
        line.Tick();
    }
}

const metro_simulation::Metro &Metro::metro() const {
    return *metro_;
}
}  // namespace core

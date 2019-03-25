#include "section.h"

namespace core {
Section::Section(metro_simulation::Section *section) : section_(section) {
}

void Section::Tick() {
}

const metro_simulation::Section &Section::section() const {
    return *section_;
}
}  // namespace core

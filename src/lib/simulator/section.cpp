#include "section.h"

namespace core {
Section::Section(proto::Section *section) : section_(section) {
}

void Section::Tick() {
}

const proto::Section &Section::section() const {
    return *section_;
}
}  // namespace core

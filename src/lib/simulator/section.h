#pragma once

#include <proto/metro.pb.h>

namespace core {
class Section {
public:
    Section(metro_simulation::Section *section);

    void Tick();

    const metro_simulation::Section &section() const;

private:
    metro_simulation::Section *section_;
};
}  // namespace core

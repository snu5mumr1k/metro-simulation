#pragma once

#include <proto/metro.pb.h>

namespace core {
class Section {
public:
    Section(metro_simulation::Section *section);

    void Tick();

private:
    metro_simulation::Section *section_;
};
}  // namespace core

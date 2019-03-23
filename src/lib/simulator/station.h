#pragma once

#include <proto/metro.pb.h>

namespace core {
class Station {
public:
    Station(metro_simulation::Station *station);

    void Tick();

private:
    metro_simulation::Station *station_;
};
}  // namespace core

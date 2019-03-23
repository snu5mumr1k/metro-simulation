#pragma once

#include <proto/config.pb.h>

#include "metro.h"

namespace core {
class Simulator {
public:
    Simulator(const metro_simulation::Config &config);

    void Tick();

    const metro_simulation::Metro &metro() const;

private:
    metro_simulation::Metro metro_data_;
    Metro metro_;
};
}  // namespace core

#pragma once

#include <proto/config.pb.h>

#include "metro.h"

namespace core {
class Simulator {
 public:
    explicit Simulator(metro_simulation::Metro metro_data);

    void Reset();
    void Reset(metro_simulation::Metro metro_data);
    void Tick(const metro_simulation::Config &config);

    const metro_simulation::Metro &metro() const;

 private:
    metro_simulation::Metro metro_data_;
    Metro metro_;
};
}  // namespace core

#pragma once

#include <proto/metro.pb.h>
#include <proto/config.pb.h>

#include <vector>

#include "line.h"

namespace core {
class Metro {
 public:
    explicit Metro(metro_simulation::Metro *metro);

    void Tick(const metro_simulation::Config &config);

    const metro_simulation::Metro &metro() const;

 private:
    metro_simulation::Metro *metro_;

    std::vector<Line> lines_;
};
}  // namespace core

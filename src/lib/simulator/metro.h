#pragma once

#include <vector>

#include <proto/metro.pb.h>

#include "line.h"

namespace core {
class Metro {
public:
    Metro(metro_simulation::Metro *metro);

    void Tick();

    const metro_simulation::Metro &metro() const;

private:
    metro_simulation::Metro *metro_;

    std::vector<Line> lines_;
};
}

#pragma once

#include <proto/metro.pb.h>

namespace core {
class Platform {
public:
    Platform(metro_simulation::Platform *platform);

    void Tick();

private:
    metro_simulation::Platform *platform_;
};
}  // namespace core

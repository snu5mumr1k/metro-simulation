#pragma once

#include <proto/metro.pb.h>

#include "path.h"

namespace core {
class Train {
public:
    Train(metro_simulation::Train *train);

    void Tick();

private:
    metro_simulation::Train *train_;

    Path path_;
};
}  // namespace core

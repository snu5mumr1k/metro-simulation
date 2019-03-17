#pragma once

#include <proto/config.pb.h>
#include <proto/metro.pb.h>


namespace metro_simulation {
void SimulatorTick(metro_simulation::Metro *metro, const metro_simulation::Config &config);
}  // namespace metro_simulation

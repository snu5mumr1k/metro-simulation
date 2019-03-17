#include "simulator.h"

namespace metro_simulation {
void SimulatorTick(metro_simulation::Metro *metro, const metro_simulation::Config &config) {
    for (auto &line : *metro->mutable_lines()) {
        for (auto &section : *line.mutable_sections()) {
            for (auto &train : *section.mutable_trains()) {
                const double path_completed = train.path_completed_part();
                train.set_path_completed_part(path_completed + 0.0001f);
            }
        }
    }
}
}  // namespace metro_simulation

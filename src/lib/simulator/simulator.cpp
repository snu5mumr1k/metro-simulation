#include <proto/metro.pb.h>

#include "simulator.h"

namespace {
metro_simulation::Metro GenerateMetro() {
    metro_simulation::Metro result;

    result.add_lines();
    auto line = result.mutable_lines(0);
    line->set_id(0);

    line->add_stations();
    line->add_stations();
    auto station1 = line->mutable_stations(0);
    auto station2 = line->mutable_stations(1);
    station1->set_id(0);
    station2->set_id(1);

    station1->add_platforms();
    auto platform1 = station1->mutable_platforms(0);
    platform1->set_id(0);

    station2->add_platforms();
    auto platform2 = station2->mutable_platforms(0);
    platform2->set_id(0);

    line->add_sections();
    auto section = line->mutable_sections(0);
    section->set_id(0);
    section->set_start_platform_id(platform1->id());
    section->set_finish_platform_id(platform2->id());

    line->add_trains();
    auto train = line->mutable_trains(0);
    train->set_id(0);
    train->set_section_completed_part(0.5);

    auto path = train->mutable_path();
    path->add_section_ids(0);

    return result;
}
}  // namespace

namespace core {
Simulator::Simulator(const metro_simulation::Config &config)
    : metro_data_(GenerateMetro()),
      metro_(&metro_data_)
{}

const metro_simulation::Metro &Simulator::metro() const {
    return metro_.metro();
}

void Simulator::Tick() {
    metro_.Tick();
}
}  // namespace core

#include <ctime>

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
    platform2->set_id(1);

    line->add_sections();
    auto section = line->mutable_sections(0);
    section->set_id(0);
    section->set_origin_platform_id(platform1->id());
    section->set_destination_platform_id(platform2->id());
    section->set_length(2000);

    line->add_trains();
    auto train = line->mutable_trains(0);
    train->set_id(0);
    train->set_meters_per_second(18);
    train->set_state(metro_simulation::Train::PLATFORM);
    train->set_platform_id(section->origin_platform_id());
    train->set_arrived_at(std::time(nullptr));

    auto path = train->mutable_path();
    auto next_step = path->mutable_next_step();
    next_step->insert({section->origin_platform_id(), section->id()});

    return result;
}
}  // namespace

namespace core {
Simulator::Simulator(metro_simulation::Metro metro_data)
    : metro_data_(metro_data),
      metro_(&metro_data_)
{}

const metro_simulation::Metro &Simulator::metro() const {
    return metro_.metro();
}

void Simulator::Reset() {
    metro_data_ = GenerateMetro();
    metro_ = Metro(&metro_data_);
}

void Simulator::Reset(metro_simulation::Metro metro_data) {
    metro_data_ = metro_data;
    metro_ = Metro(&metro_data_);
}

void Simulator::Tick() {
    metro_.Tick();
}
}  // namespace core

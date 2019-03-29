#pragma once

#include <unordered_map>

#include <proto/metro.pb.h>
#include <proto/config.pb.h>

#include "platform.h"
#include "section.h"
#include "station.h"
#include "train.h"

namespace core {
class Line {
public:
    Line(metro_simulation::Line *line);

    void Tick(const metro_simulation::Config &config);

private:
    metro_simulation::Line *line_;

    std::unordered_map<int64_t, Section> sections_;
    std::unordered_map<int64_t, Station> stations_;

    std::unordered_map<int64_t, Platform> platforms_;
    std::unordered_map<int64_t, Train> trains_;
};
}  // namespace core

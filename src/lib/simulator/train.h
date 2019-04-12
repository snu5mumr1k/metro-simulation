#pragma once

#include <proto/metro.pb.h>
#include <proto/config.pb.h>

#include <optional>
#include <unordered_map>

#include "path.h"
#include "section.h"

namespace core {
class Train {
 public:
    Train(metro_simulation::Train *train, const std::unordered_map<int64_t, Section> &sections);

    void Tick(const metro_simulation::Config &config);

 private:
    metro_simulation::Train *train_;
    Path path_;
    std::optional<const Section> current_section_;
};
}  // namespace core

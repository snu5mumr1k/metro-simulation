#pragma once

#include <optional>

#include <proto/metro.pb.h>

namespace core {
class Path {
public:
    Path(const metro_simulation::Path &path);

    std::optional<int64_t> NextSectionId(int64_t section_id) const;

private:
    const metro_simulation::Path &path_;
};
}  // namespace core

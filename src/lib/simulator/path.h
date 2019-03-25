#pragma once

#include <optional>

#include <proto/metro.pb.h>

#include "section.h"

namespace core {
class Path {
public:
    Path(const metro_simulation::Path &path, const std::unordered_map<int64_t, Section> &sections);

    std::optional<const Section> FindNextSection(int64_t platform_id) const;

private:
    const metro_simulation::Path &path_;

    const std::unordered_map<int64_t, Section> &sections_;
};
}  // namespace core

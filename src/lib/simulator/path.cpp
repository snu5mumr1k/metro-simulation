#include "path.h"

namespace core {
Path::Path(const metro_simulation::Path &path) : path_(path)
{}

std::optional<int64_t> Path::NextSectionId(int64_t section_id) const {
    bool found = false;
    std::optional<int64_t> result;
    for (int64_t s : path_.section_ids()) {
        if (found) {
            result = s;
            break;
        }
        if (s == section_id) {
            found = true;
        }
    }

    return result;
}
}  // namespace core

#include "path.h"

namespace core {
Path::Path(const proto::Path &path, const std::unordered_map<int64_t, Section> &sections)
    : path_(path),
      sections_(sections) {
}

std::optional<const Section> Path::FindNextSection(int64_t platform_id) const {
    const auto section_id = path_.next_step().find(platform_id);
    if (section_id != path_.next_step().end()) {
        return sections_.at(section_id->second);
    }
    return {};
}
}  // namespace core

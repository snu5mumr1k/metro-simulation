#pragma once

#include <proto/metro.pb.h>

#include <lib/simulator/section.h>

#include <optional>
#include <unordered_map>

namespace core {
class Path {
 public:
  Path(const proto::Path &path, const std::unordered_map<int64_t, Section> &sections);

  std::optional<const Section> FindNextSection(int64_t platform_id) const;
  Section FirstSection() const;

 private:
  const proto::Path &path_;

  const std::unordered_map<int64_t, Section> &sections_;
};
}  // namespace core

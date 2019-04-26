#pragma once

#include <proto/metro.pb.h>
#include <proto/config.pb.h>

#include <lib/simulator/path.h>
#include <lib/simulator/section.h>

#include <optional>
#include <unordered_map>

namespace core {
class Train {
 public:
  Train(proto::Train *train, const std::unordered_map<int64_t, Section> &sections);

  void Tick(const proto::Config &config);

 private:
  proto::Train *train_;
  Path path_;
  std::optional<const Section> current_section_;
};
}  // namespace core

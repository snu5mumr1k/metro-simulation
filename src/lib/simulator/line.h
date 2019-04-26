#pragma once

#include <proto/metro.pb.h>
#include <proto/config.pb.h>

#include <lib/simulator/platform.h>
#include <lib/simulator/section.h>
#include <lib/simulator/station.h>
#include <lib/simulator/train.h>

#include <unordered_map>

namespace core {
class Line {
 public:
  explicit Line(proto::Line *line);

  void Tick(const proto::Config &config);

 private:
  proto::Line *line_;

  std::unordered_map<int64_t, Section> sections_;
  std::unordered_map<int64_t, Station> stations_;

  std::unordered_map<int64_t, Platform> platforms_;
  std::unordered_map<int64_t, Train> trains_;
};
}  // namespace core

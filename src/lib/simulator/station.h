#pragma once

#include <proto/metro.pb.h>

namespace core {
class Station {
 public:
  explicit Station(proto::Station *station);

  void Tick();

 private:
  proto::Station *station_;
};
}  // namespace core

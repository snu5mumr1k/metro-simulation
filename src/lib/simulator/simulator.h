#pragma once

#include <proto/config.pb.h>
#include <proto/metro.pb.h>

#include <lib/simulator/metro.h>

namespace core {
class Simulator {
 public:
  explicit Simulator(proto::Metro *metro_data);

  void Reset(const proto::Config &config);
  void Reset(proto::Metro metro_data);
  void Tick(const proto::Config &config);

  const proto::Metro &metro() const;

 private:
  proto::Metro metro_data_;
  Metro metro_;
};
}  // namespace core

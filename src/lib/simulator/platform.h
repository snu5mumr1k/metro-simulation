#pragma once

#include <proto/metro.pb.h>

namespace core {
class Platform {
 public:
  explicit Platform(proto::Platform *platform);

  void Tick();

 private:
  proto::Platform *platform_;
};
}  // namespace core

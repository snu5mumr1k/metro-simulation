#pragma once

#include <proto/metro.pb.h>
#include <proto/config.pb.h>

#include <vector>

#include "line.h"

namespace core {
class Metro {
 public:
    explicit Metro(proto::Metro *metro);

    void Tick(const proto::Config &config);

    const proto::Metro &metro() const;

 private:
    proto::Metro *metro_;

    std::vector<Line> lines_;
};
}  // namespace core

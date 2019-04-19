#pragma once

#include <proto/metro.pb.h>

namespace core {
class Section {
 public:
    explicit Section(proto::Section *section);

    void Tick();

    const proto::Section &section() const;

 private:
    proto::Section *section_;
};
}  // namespace core

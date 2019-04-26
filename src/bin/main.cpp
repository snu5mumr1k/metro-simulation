#include <chrono>
#include <fstream>
#include <thread>

#include <google/protobuf/text_format.h>

#include <proto/config.pb.h>
#include <proto/metro.pb.h>

#include <lib/graphics/adapter/sdl_adapter.h>
#include <lib/simulator/simulator.h>
#include <lib/util/singleton/singleton.h>
#include <lib/util/id_generator/id_generator.h>

namespace {
template<class TProto>
void Dump(const TProto& proto, const std::string& filename) {
  std::ofstream out(filename);
  proto.SerializeToOstream(&out);
}

template<class TProto>
TProto Load(const std::string& filename) {
  std::ifstream in(filename);
  TProto proto;
  proto.ParseFromIstream(&in);
  return proto;
}

void InitGenerators(const proto::Metro &metro) {
  util::Singleton<util::IdGenerator<proto::Line>>()->ResetStorage(metro.lines().begin(), metro.lines().end());
  for (const auto &line : metro.lines()) {
    util::Singleton<util::IdGenerator<proto::Station>>()->AddMany(line.stations().begin(), line.stations().end());
    util::Singleton<util::IdGenerator<proto::Section>>()->AddMany(line.sections().begin(), line.sections().end());
    for (const auto &station : line.stations()) {
      util::Singleton<util::IdGenerator<proto::Platform>>()->AddMany(station.platforms().begin(), station.platforms().end());
    }
    util::Singleton<util::IdGenerator<proto::Train>>()->AddMany(line.trains().begin(), line.trains().end());
  }
}
}  // namespace

int main() {
  graphics::SDL *sdl = util::Singleton<graphics::SDL>();

  bool quit = false;
  proto::Config config = Load<proto::Config>("../config.json");
  auto metro = Load<proto::Metro>("../metro.json");
  InitGenerators(metro);
  core::Simulator simulator(&metro);
  while (!quit) {
    sdl->InitFrame();
    const auto action = sdl->DrawInterface();
    sdl->Draw(config, simulator.metro());
    config = sdl->EditConfig(config);
    sdl->EditMetro(&metro);
    sdl->FinishFrame();

    switch (action) {
      case graphics::SDL::Action::ResetToBeginning: {
        simulator.Reset(metro);
        break;
      }
      case graphics::SDL::Action::ResetToDefaults: {
        simulator.Reset(config);
        break;
      }
      case graphics::SDL::Action::Quit: {
        quit = true;
        break;
      }
      case graphics::SDL::Action::Idle: {
        break;
      }
    }
    simulator.Refresh();
    for (int i = 0; i < config.ticks_per_frame(); ++i) {
      simulator.Tick(config);
      const double new_timestamp = config.current_simulation_timestamp() + config.seconds_per_tick();
      config.set_current_simulation_timestamp(new_timestamp);
    }

    const auto sleep_time = std::chrono::milliseconds(1000 / config.frames_per_second());
    std::this_thread::sleep_for(sleep_time);
  }
  Dump(simulator.metro(), "../metro.json");
  Dump(config, "../config.json");
}

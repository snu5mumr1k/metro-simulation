#include <chrono>
#include <fstream>
#include <thread>

#include <google/protobuf/text_format.h>

#include <proto/config.pb.h>
#include <proto/metro.pb.h>

#include <lib/graphics/adapter/sdl_adapter.h>
#include <lib/simulator/simulator.h>
#include <lib/util/singleton/singleton.h>


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

int main() {
    graphics::SDL *sdl = Singleton<graphics::SDL>();

    bool quit = false;
    metro_simulation::Config config = Load<metro_simulation::Config>("../config.json");
    auto metro = Load<metro_simulation::Metro>("../metro.json");
    core::Simulator simulator(metro);
    while (!quit) {
        sdl->InitFrame();
        sdl->Draw(config, simulator.metro());
        config = sdl->EditConfig(config);
        metro = sdl->EditMetro(metro);
        const auto action = sdl->DrawInterface();
        sdl->FinishFrame();

        switch (action) {
            case graphics::SDL::Action::ResetToBeginning: {
                simulator.Reset(metro);
                break;
            }
            case graphics::SDL::Action::ResetToDefaults: {
                simulator.Reset();
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

        for (int i = 0; i < config.ticks_per_frame(); ++i) {
            simulator.Tick(config);
            const int64_t new_timestamp = config.current_simulation_timestamp() + config.tick_simulation_seconds();
            config.set_current_simulation_timestamp(new_timestamp);
        }

        const auto sleep_time = std::chrono::milliseconds(static_cast<int64_t>(1.0 / config.frames_per_second()));
        std::this_thread::sleep_for(sleep_time);
    }
    Dump(simulator.metro(), "../metro.json");
    Dump(config, "../config.json");
}

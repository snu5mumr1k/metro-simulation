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
    using namespace std::chrono_literals;

    graphics::SDL *sdl = Singleton<graphics::SDL>();

    bool quit = false;
    const auto sleep_time = 33ms;

    std::optional<metro_simulation::Config> config = Load<metro_simulation::Config>("../config.json");
    const auto metro = Load<metro_simulation::Metro>("../metro.json");
    core::Simulator simulator(metro);
    while (!quit) {
        sdl->ClearBuffer();
        auto new_config = sdl->DrawInterface(*config, simulator.metro());
        sdl->Draw(*config, simulator.metro());
        sdl->SwapBuffers();

        if (!new_config) {
            quit = true;
        } else {
            simulator.Tick();
        }

        config.swap(new_config);

        if (config->reset_to_beginning()) {
            simulator.Reset(metro);
            config->set_reset_to_beginning(false);
        } else if (config->reset_to_defaults()) {
            simulator.Reset();
            config->set_reset_to_defaults(false);
        }

        std::this_thread::sleep_for(sleep_time);
    }
    Dump(simulator.metro(), "../metro.json");
    Dump(*config, "../config.json");
}

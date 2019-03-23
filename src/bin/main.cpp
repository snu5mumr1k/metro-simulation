#include <chrono>
#include <fstream>
#include <thread>

#include <google/protobuf/text_format.h>

#include <proto/config.pb.h>
#include <proto/metro.pb.h>

#include <lib/graphics/adapter/sdl_adapter.h>
#include <lib/simulator/simulator.h>
#include <lib/util/singleton/singleton.h>

void DumpMetro(const metro_simulation::Metro& metro, const std::string& filename) {
    std::ofstream out(filename);
    metro.SerializeToOstream(&out);
}

int main() {
    using namespace std::chrono_literals;

    graphics::SDL *sdl = Singleton<graphics::SDL>();

    bool quit = false;
    const auto sleep_time = 1s;
    std::optional<metro_simulation::Config> config = metro_simulation::Config();
    core::Simulator simulator(*config);
    while (!quit) {
        config = sdl->DrawInterface(*config);
        if (!config) {
            quit = true;
        } else {
            simulator.Tick();
        }

        sdl->Draw(*config, simulator.metro());

        sdl->SwapBuffers();

        std::this_thread::sleep_for(sleep_time);
    }
    DumpMetro(simulator.metro(), "./metro.json");
}

#include <lib/graphics/adapter/sdl_adapter.h>
#include <lib/util/singleton/singleton.h>
#include <proto/config.pb.h>
#include <proto/metro.pb.h>

#include <chrono>
#include <thread>

int main() {
    using namespace std::chrono_literals;

    graphics::SDL *sdl = Singleton<graphics::SDL>();

    bool quit = false;
    const auto sleep_time = 30ms;
    std::optional<metro_simulation::Config> config = metro_simulation::Config();
    metro_simulation::Metro metro;
    while (!quit) {
        config = sdl->DrawInterface(*config);
        if (!config) {
            quit = true;
        }

        sdl->Draw(*config, metro);

        sdl->SwapBuffers();

        std::this_thread::sleep_for(sleep_time);
    }
}

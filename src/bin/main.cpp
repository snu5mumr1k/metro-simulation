#include <lib/graphics/adapter/sdl_adapter.h>
#include <lib/util/singleton/singleton.h>

#include <chrono>
#include <thread>

int main() {
    using namespace std::chrono_literals;

    graphics::SDL *sdl = Singleton<graphics::SDL>();

    bool quit = false;
    const auto sleep_time = 30ms;
    while (!quit) {
        quit = sdl->HandleEvents();

        std::this_thread::sleep_for(sleep_time);
    }
}

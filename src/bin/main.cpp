#include <lib/graphics/adapter/sdl_adapter.h>
#include <lib/util/singleton/singleton.h>
#include <proto/config.pb.h>
#include <proto/metro.pb.h>

#include <google/protobuf/text_format.h>

#include <chrono>
#include <fstream>
#include <thread>

void DumpMetro(const metro_simulation::Metro& metro, const std::string& filename) {
    std::ofstream out(filename);
    metro.SerializeToOstream(&out);
}

metro_simulation::Metro GenerateMetro() {
    metro_simulation::Metro result;

    result.add_lines();
    auto line = result.mutable_lines(0);
    line->set_id(0);

    line->add_stations();
    line->add_stations();
    auto station1 = line->mutable_stations(0);
    auto station2 = line->mutable_stations(1);
    station1->set_id(0);
    station2->set_id(1);

    station1->add_platforms();
    auto platform1 = station1->mutable_platforms(0);
    platform1->set_id(0);

    station2->add_platforms();
    auto platform2 = station2->mutable_platforms(0);
    platform2->set_id(0);

    line->add_sections();
    auto section = line->mutable_sections(0);
    section->set_id(0);
    section->set_start_platform_id(platform1->id());
    section->set_finish_platform_id(platform2->id());

    section->add_trains();
    auto train = section->mutable_trains(0);
    train->set_id(0);
    train->set_path_completed_part(0.5);

    return result;
}

int main() {
    using namespace std::chrono_literals;

    graphics::SDL *sdl = Singleton<graphics::SDL>();

    bool quit = false;
    const auto sleep_time = 30ms;
    std::optional<metro_simulation::Config> config = metro_simulation::Config();
    metro_simulation::Metro metro = GenerateMetro();
    while (!quit) {
        config = sdl->DrawInterface(*config);
        if (!config) {
            quit = true;
        } else {
            Simulator->Tick(metro, config);
        }

        sdl->Draw(*config, metro);

        sdl->SwapBuffers();

        std::this_thread::sleep_for(sleep_time);
    }
    DumpMetro(metro, "./metro.json");
}

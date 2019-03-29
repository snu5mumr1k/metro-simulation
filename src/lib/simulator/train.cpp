#include "train.h"

namespace {
    constexpr int64_t SLEEP_TIME = 30;
}

namespace core {
Train::Train(metro_simulation::Train *train, const std::unordered_map<int64_t, Section> &sections)
    : train_(train),
      path_(train->path(), sections),
      current_section_() {
}

void Train::Tick(const metro_simulation::Config &config) {
    switch (train_->state()) {
        case metro_simulation::Train::PLATFORM: {
            if (config.current_simulation_timestamp() - train_->arrived_at() < SLEEP_TIME) {
                return;
            }

            const auto section_maybe = path_.FindNextSection(train_->platform_id());
            if (section_maybe) {
                current_section_.emplace(*section_maybe);

                const auto section = current_section_->section();
                train_->set_platform_id(section.destination_platform_id());
                train_->set_section_completed_meters(0);
                train_->set_section_id(section.id());
                train_->set_state(metro_simulation::Train::SECTION);
            } else {
                current_section_.reset();
                train_->set_state(metro_simulation::Train::IDLE);
            }
            break;
        }
        case metro_simulation::Train::SECTION: {
            const int64_t completed = train_->section_completed_meters() + train_->meters_per_second();
            const int64_t section_length = current_section_->section().length();
            if (completed >= section_length) {
                train_->set_state(metro_simulation::Train::PLATFORM);
                train_->set_arrived_at(config.current_simulation_timestamp());
            }
            train_->set_section_completed_meters(completed);
            break;
        }
        default: {
            break;
        }
    }
}
}  // namespace core

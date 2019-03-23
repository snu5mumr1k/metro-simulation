#include "train.h"

namespace {
    const double rate = 0.33;
}

namespace core {
Train::Train(metro_simulation::Train *train) : train_(train), path_(train->path()) {
}

void Train::Tick() {
    if (train_->state() == metro_simulation::Train::PLATFORM) {
        train_->set_section_completed_part(0.0);
        const auto section_id = path_.NextSectionId(train_->section_id());
        if (section_id) {
            train_->set_section_id(*section_id);
            train_->set_state(metro_simulation::Train::SECTION);
        } else {
            train_->set_state(metro_simulation::Train::IDLE);
        }
    } else {
        const double section_completed_part = train_->section_completed_part() + rate;
        if (section_completed_part >= 1.0) {
            train_->set_section_completed_part(1.0);
            train_->set_state(metro_simulation::Train::PLATFORM);
        } else {
            train_->set_section_completed_part(section_completed_part);
        }
    }
}
}  // namespace core

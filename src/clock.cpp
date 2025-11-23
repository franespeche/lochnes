#include "clock.h"

void Clock::subscribe(IClockConsumer *c) {
  consumers.push_back(c);
}

void Clock::tick() {
  for (auto *c : consumers) {
    c->tick();
  }
  master_cycles++;
}


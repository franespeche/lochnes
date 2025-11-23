#pragma once

#include <vector>
#include "core/bus.h"
#include "core/cpu6502.h"
#include "core/clock.h"

struct System {
  Bus bus;
  CPU6502 cpu;
  Clock clock;

  System();
  void load_rom(const std::vector<uint8_t> &data);
  void reset();
  void run();
};


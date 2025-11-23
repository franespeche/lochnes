#pragma once

#include <vector>
#include "bus.h"
#include "cpu6502.h"
#include "clock.h"

struct System {
  Bus bus;
  CPU6502 cpu;
  Clock clock;

  System();
  void load_rom(const std::vector<uint8_t> &data);
  void reset();
  void run();
};

